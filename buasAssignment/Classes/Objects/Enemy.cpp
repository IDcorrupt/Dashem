#include "Enemy.h"
#include <iostream>


//vector normalizer
sf::Vector2f NormalizeVector(sf::Vector2f vector) {
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    sf::Vector2f normalizedVector;
    normalizedVector.x = vector.x / magnitude;
    normalizedVector.y = vector.y / magnitude;
    return normalizedVector;
}


//constructor
Enemy::Enemy(EnemyType spawntype, const sf::Texture& Textures) {
    int xIndex = 0;
    int yIndex = 0;
    switch (spawntype)
    {
    case Normal:
        type = Normal;
        health = 2;
        damage = 1;
        speed = 0.15f;
        attackCooldown = 2000.0f;
        
        sprite.setTexture(Textures);
        sprite.scale(3, 3);
        xIndex = 0;
        yIndex = 13;
        sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        sprite.setOrigin(16, 18);

        hitBox.setSize(sf::Vector2f(45, 65));
        hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
        hitBox.setFillColor(sf::Color::Transparent);
        hitBox.setOutlineColor(sf::Color::Red);
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
        hitBox.setOutlineColor(sf::Color::Red);
        hitBox.setOutlineThickness(2);
        hitBox.setPosition(sprite.getPosition());
        break;

    case Elite:
        type = Elite;
        health = 5;
        damage = 2;
        speed = 0.2f;
        attackCooldown = 1000.0f;

        sprite.setTexture(Textures);
        sprite.scale(5, 5);
        xIndex = 0;
        yIndex = 6;
        sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        sprite.setOrigin(16, 24);

        hitBox.setSize(sf::Vector2f(150, 140));
        hitBox.setOrigin(hitBox.getSize().x / 2 + 10, hitBox.getSize().y / 2 + 30);
        hitBox.setFillColor(sf::Color::Transparent);
        hitBox.setOutlineColor(sf::Color::Red);
        hitBox.setOutlineThickness(2);
        hitBox.setPosition(sprite.getPosition());
        break;

    default:
        std::cout << "how." << std::endl;
        dead = true;
        //[SELF NOTE]  DESPAWN ENEMY IF DEFAULT CALLED (shouldn't happen tho)
        break;
    }

}

void Enemy::Update(sf::Vector2f target, float delta, sf::Vector2f playerMovement)
{
    sf::Vector2f displacement;
    if (attacking) {
        float reduction = 0.3f;
        if (type == Normal || type == Elite) {
            //exit attack sequence if slow enough
            if (std::sqrt(attackVelocity.x * attackVelocity.x + attackVelocity.y * attackVelocity.y) < 1.5) {
                attacking = false;
                attackVelocity = sf::Vector2f(0, 0);
                attackDelta = attackCooldown;
                return;
            }
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
            std::cout << "asd" << std::endl;

            if (bulletsRemaining == 0) {
                attacking = false;
                attackDelta = attackCooldown;
            }
            else if (shootDelta <= 0) {
                ShooterAttack(target, delta);
            }
            
            //"nullify" displacement - shooter remains in place while shooting
            displacement = sprite.getPosition();
        }
    }
    else {
        sf::Vector2f movementvector = NormalizeVector(target - sprite.getPosition()) * speed;
        displacement = sprite.getPosition() + movementvector * delta;
        sf::Vector2f distance = target - sprite.getPosition();
        //check for attack availability
        switch (type)
        {
        case Enemy::Normal:
            if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < 160 && attackDelta <= 0 && !attacking) {
                NormalAttack(target);
            }
            break;
        case Enemy::Shooter:
            if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < 400 && attackDelta <= 0 && !attacking) {
                std::cout << "in range" << std::endl;
                bulletsRemaining = shootAmount;
                attacking = true;
                ShooterAttack(target, delta);
            }
            else if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < 400) {
                //stop moving if in attack range
                displacement = sprite.getPosition();
            }
            break;
        case Enemy::Elite:
            if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < 5 && attackDelta <= 0 && !attacking)
                EliteAttack(target);
            break;
        default:
            break;
        }
    }



    int i = 0;
    for (Projectile& bullet : projectiles) {
        if (!bullet.hit)
            bullet.Shoot(delta, playerMovement);
        else
            projectiles.erase(projectiles.begin() + i);
        i++;
    }



    sprite.setPosition(displacement + playerMovement);
    hitBox.setPosition(sprite.getPosition());
    //cooldowns
    if (attackDelta > 0)
        attackDelta -= delta;
    else
        attackDelta = 0;
    if (shootDelta > 0)
        shootDelta -= delta;
    else
        shootDelta = 0;
}


void Enemy::Damaged()
{

}

void Enemy::Die()
{

}

//attack types
void Enemy::NormalAttack(sf::Vector2f target) {
    attackVelocity = (NormalizeVector(target - sprite.getPosition())) * (speed*20);
    attacking = true;
}
void Enemy::ShooterAttack(sf::Vector2f target, float delta) {
    bulletsRemaining--;
    shootDelta = shootCooldown;
    Projectile bullet;
    bullet.sprite.setPosition(this->sprite.getPosition());
    sf::Vector2f shootDir = target - bullet.sprite.getPosition();
    bullet.setVector(NormalizeVector(shootDir));
    projectiles.push_back(bullet);
}
void Enemy::EliteAttack(sf::Vector2f target) {

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