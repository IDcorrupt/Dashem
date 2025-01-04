#include "Enemy.h"
#include <iostream>
#include "../Mechanics/Math.h"
#include "Player.h"

//constructor
Enemy::Enemy(EnemyType spawntype, const sf::Texture& Textures, std::shared_ptr<sf::Texture> projTexture) :projTexture(projTexture) {
    int xIndex = 0;
    int yIndex = 0;
    hurtTimer;

    switch (spawntype)
    {
    case Normal:
        //general values
        type = Normal;
        health = 2;
        damage = 1;
        speed = 0.15f;
        attackCooldown = 2000.0f;
        
        //sprite setup
        sprite.setTexture(Textures);
        sprite.scale(3, 3);
        xIndex = 0;
        yIndex = 13;
        sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        sprite.setOrigin(16, 18);
        
        //hitbox setup
        hitBox.setSize(sf::Vector2f(45, 65));
        hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
        hitBox.setFillColor(sf::Color::Transparent);
        hitBox.setOutlineColor(sf::Color::Blue);
        hitBox.setOutlineThickness(2);
        hitBox.setPosition(sprite.getPosition());
        break;

    case Shooter:
        type = Shooter;
        health = 1;
        damage = 1;
        speed = 0.1f;
        attackCooldown = 5000.0f;

        sprite.setTexture(Textures);
        sprite.scale(4, 4);
        xIndex = 0;
        yIndex = 0;
        sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        sprite.setOrigin(16, 20);

        hitBox.setSize(sf::Vector2f(60, 60));
        hitBox.setOrigin(hitBox.getSize().x / 2 - 8, hitBox.getSize().y / 2 + 30);
        hitBox.setFillColor(sf::Color::Transparent);
        hitBox.setOutlineColor(sf::Color::Blue);
        hitBox.setOutlineThickness(2);
        hitBox.setPosition(sprite.getPosition());
        break;

    case Elite:
        type = Elite;
        health = 5;
        damage = 2;
        speed = 0.2f;
        attackCooldown = 2000.0f;

        sprite.setTexture(Textures);
        sprite.scale(5, 5);
        xIndex = 0;
        yIndex = 6;
        sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        sprite.setOrigin(16, 24);

        hitBox.setSize(sf::Vector2f(150, 140));
        hitBox.setOrigin(hitBox.getSize().x / 2 + 10, hitBox.getSize().y / 2 + 30);
        hitBox.setFillColor(sf::Color::Transparent);
        hitBox.setOutlineColor(sf::Color::Blue);
        hitBox.setOutlineThickness(2);
        hitBox.setPosition(sprite.getPosition());
        break;

    default:
        std::cout << "how." << std::endl;
        isDead = true;
        //[SELF NOTE]  DESPAWN ENEMY IF DEFAULT CALLED (shouldn't happen tho)
        break;
    }

}

void Enemy::Update(sf::Vector2f target, float delta, sf::Vector2f playerMovement, Player& player, std::vector<Enemy> otherEnemies)
{
    if (!isDead || true) { // [DEBUG]  |  temporary "|| true" so enemies don't break 
        //set displacement default value
        sf::Vector2f displacement = sprite.getPosition();

        //detect for incoming hurt enemies (chain mechanic)
        for (Enemy otherEnemy : otherEnemies) {
            if (Math::CheckHitboxCollision(sprite.getGlobalBounds(), otherEnemy.sprite.getGlobalBounds()) && !isHurt && otherEnemy.isHurt) {
                //if enemy gets hit by other enemy that is hurt (this one isnt)
                Damaged(otherEnemy.sprite);
            }
        }


        //check for incoming attack
        if (Math::CheckHitboxCollision(player.sprite.getGlobalBounds(), sprite.getGlobalBounds()) && player.isDashing && !isHurt) {
            //requirements: colliding with player, player is attacking, enemy isn't already attacked recently
            Damaged(player.sprite);
        }
        //hurt knockback sequence
        else if (isHurt) {
            displacement = sprite.getPosition() + hurtVelocity * delta;
        }
        //attack sequence
        else if (isAttacking) {
            float reduction = 0.3f;
            if (type == Normal || type == Elite) {
                //exit attack sequence if slow enough
                if (std::sqrt(attackVelocity.x * attackVelocity.x + attackVelocity.y * attackVelocity.y) < 1.5) {
                    CancelAttack();
                    return;
                }
                //gradually slow attack speed
                if (attackVelocity.x > 0) {
                    attackVelocity.x = std::max(0.0f, attackVelocity.x - reduction);
                }
                else {
                    attackVelocity.x = std::min(0.0f, attackVelocity.x + reduction);
                }

                if (attackVelocity.y > 0) {
                    attackVelocity.y = std::max(0.0f, attackVelocity.y - reduction);
                }
                else {
                    attackVelocity.y = std::min(0.0f, attackVelocity.y + reduction);
                }
                displacement = sprite.getPosition() + attackVelocity * delta;
            }
            else {
                //if type is shooter
                if (bulletsRemaining == 0) {
                    CancelAttack();
                    return;
                }
                else if (shootDelta <= 0) {
                    ShooterAttack(target, delta);
                }
            }
        }
        //shooter has slightly different mechanics - doesn't freeze after attacking since it is ranged -> attackdelta check at different point
        else if(attackDelta <= 0 || type == Shooter) {
            //movement
        
            sf::Vector2f movementvector = Math::NormalizeVector(target - sprite.getPosition()) * speed;
            displacement = sprite.getPosition() + movementvector * delta;
        
            //check for attack availability
            sf::Vector2f distance = target - sprite.getPosition();
            switch (type)
            {
            case Enemy::Normal:
                if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < 160 && !isAttacking) {
                    isAttacking = true;
                    NormalAttack(target);
                }
                break;
            case Enemy::Elite:
                if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < 320 && !isAttacking) {
                    isAttacking = true;
                    EliteAttack(target);
                }
                break;
            case Enemy::Shooter:
                if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < 400 && !isAttacking && attackDelta <= 0) {
                    bulletsRemaining = shootAmount;
                    isAttacking = true;
                    ShooterAttack(target, delta);
                }
                else if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < 400) {
                    //stop moving if in attack range
                    displacement = sprite.getPosition();
                }
                break;
            default:
                break;
            }

        }
        //projectile movement & despawning
        int i = 0;
        for (Projectile& bullet : projectiles) {
            if (!bullet.hit)
                bullet.Shoot(delta, playerMovement, player);
            else
                projectiles.erase(projectiles.begin() + i);
            i++;
        }


        //update sprite & hitbox position
        sprite.setPosition(displacement + playerMovement);
        hitBox.setPosition(sprite.getPosition());
        //cooldowns
        if (attackDelta > 0)
            attackDelta -= delta;
        else {
            attackDelta = 0;
        }
        if (shootDelta > 0)
            shootDelta -= delta;
        else
            shootDelta = 0;
        if (isHurt && hurtTimer.getElapsedTime().asSeconds() > 0.2) {
            isHurt = false;
            hurtVelocity = sf::Vector2f(0, 0);
        }

    }
    else {
        //dead
    }
    
    //debug coloring
    if (isHurt)
        hitBox.setOutlineColor(sf::Color::Red);
    else if (isAttacking)
        hitBox.setOutlineColor(sf::Color::Blue);
    else
        hitBox.setOutlineColor(sf::Color::Green);
}

void Enemy::Damaged(sf::Sprite initilaizer)
{
    CancelAttack();
    isHurt = true;
    hurtTimer.restart();
    hurtVelocity = Math::NormalizeVector(sprite.getPosition() - initilaizer.getPosition()) * (speed * 15);
    health--;
    if (health == 0)
        isDead = true;
}

void Enemy::CancelAttack() {
    isAttacking = false;
    bulletsRemaining = 0;
    attackVelocity = sf::Vector2f(0, 0);
    attackDelta = attackCooldown;
}




void Enemy::Die()
{

}

//attack types
void Enemy::NormalAttack(sf::Vector2f target) {
    attackVelocity = (Math::NormalizeVector(target - sprite.getPosition())) * (speed*20);
}
void Enemy::ShooterAttack(sf::Vector2f target, float delta) {
    bulletsRemaining--;
    shootDelta = shootCooldown;

    Projectile bullet(projTexture);
    bullet.sprite.setPosition(sprite.getPosition() + sf::Vector2f(20,-17));
    sf::Vector2f shootDir = target - bullet.sprite.getPosition();
    bullet.setVector(Math::NormalizeVector(shootDir));
    projectiles.push_back(bullet);
}
void Enemy::EliteAttack(sf::Vector2f target) {
    attackVelocity = (Math::NormalizeVector(target - sprite.getPosition())) * (speed * 25);
}
//getters
int Enemy::getHealth() { return health; }
bool Enemy::getHurt() { return isHurt; }


void Enemy::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(hitBox);
    if (type == Shooter) {
        for (Projectile& bullet : projectiles) {
            bullet.Draw(window);
        }
    }
}

