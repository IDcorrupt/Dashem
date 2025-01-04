#include "Player.h"
#include "../Mechanics/Math.h"
#include "Enemy.h"

//contructor
Player::Player(sf::Vector2f gameRes)
{
    Player::health = health;
    Player::healthMax = healthMax;
    Player::speed = speed;
    Player::healCooldown = healCooldown;
    Player::healDelta = 0;
    Player::dashCooldown = dashCooldown;
    Player::dashDelta = 0;
    Player::isDead = false;
    Player::sprite.setPosition(gameRes.x / 2, gameRes.y / 2);
    Player::hurtTimer;

    hitBox.setSize(sf::Vector2f(50, 70));
    hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
    hitBox.setFillColor(sf::Color::Transparent);
    hitBox.setOutlineColor(sf::Color::White);
    hitBox.setOutlineThickness(2);
    hitBox.setPosition(sprite.getPosition());

    if (Texture.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Players/No_Outline/player_blue_x1.png"))
    {
        std::cout << "player texture set successfully..." << std::endl;
        sprite.setTexture(Texture);
        sprite.scale(sf::Vector2f(4, 4));
        //selecting sprite from loaded spritesheet
        int xIndex = 0;
        int yIndex = 0;
        sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        
        sprite.setOrigin(16, 24);

    }
    else
    {
        std::cout << "player texture failed to load..." << std::endl;
    }
}

//functions
sf::Vector2f Player::Update(float delta, sf::Vector2f dashDir, std::vector<Enemy> enemies)
{
    //set displacement default value
    sf::Vector2f displacement(0,0);

    if (isHurt) {
        displacement = hurtVelocity;
    }
    else {
        //check for incoming attacks
        for (Enemy enemy : enemies) {
            if (Math::CheckHitboxCollision(sprite.getGlobalBounds(), enemy.sprite.getGlobalBounds()) && enemy.isAttacking && !isDashing) {
                Damaged(enemy.sprite, false);
            }
        }
        if (isDashing) {

            //exit dash if slow enough
            if (std::sqrt(dashVelocity.x * dashVelocity.x + dashVelocity.y * dashVelocity.y) < 1.2) {
                isDashing = false;
                dashVelocity = sf::Vector2f(0, 0);
                dashDelta = dashCooldown;
                return sf::Vector2f(0, 0);
            }

            //reduce velocity
            float reduction = 0.2f;
            if (dashVelocity.x > 0) {
                dashVelocity.x = std::max(0.0f, dashVelocity.x - reduction);
            }
            else {
                dashVelocity.x = std::min(0.0f, dashVelocity.x + reduction);
            }

            if (dashVelocity.y > 0) {
                dashVelocity.y = std::max(0.0f, dashVelocity.y - reduction);
            }
            else {
                dashVelocity.y = std::min(0.0f, dashVelocity.y + reduction);
            }

            //return early, cut off all other movement
            return -dashVelocity * delta;
        }
        else {
            //only allow movement if not currently dashing (attacking)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isDashing && !(dashDelta > 0)) {
                //initiate dash
                dashVelocity = Math::NormalizeVector(dashDir) * (speed * 15);
                isDashing = true;
            }

            //get inputs & record displacement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                displacement += sf::Vector2f(0, -speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                displacement += sf::Vector2f(-speed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                displacement += sf::Vector2f(0, speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                displacement += sf::Vector2f(speed, 0);
        }
    }
    //cooldowns
    if (dashDelta > 0)
        dashDelta -= delta;
    else
        dashDelta = 0;
    if (isHurt && hurtTimer.getElapsedTime().asSeconds() > 0.1)
        isHurt = false;
    HealTick(delta);
    //debug coloring
    if (isHurt)
        hitBox.setOutlineColor(sf::Color::Red);
    else if (isDashing)
        hitBox.setOutlineColor(sf::Color::Blue);
    else
        hitBox.setOutlineColor(sf::Color::White);

    //apply movement
    return -displacement * delta;

    //sprite facing
    // [SELF NOTE]  |  negative scale didnt work -> do this later when you know how

}
void Player::Damaged(sf::Sprite initilaizer, bool isProjectile)
{
    std::cout << "got hit" << std::endl;
    if (!isProjectile) {
        hurtTimer.restart();
        isHurt = true;
        hurtVelocity = Math::NormalizeVector(sprite.getPosition() - initilaizer.getPosition()) * (speed * 10);
    }
    health--;
    if (health == 0)
        isDead = true;
}
void Player::HealTick(float delta) {
    if (health == healthMax)
        healDelta = healCooldown;
    if (health != healthMax && healDelta > 0)
        healDelta -= delta;
    else if(health < healthMax){
        health++;
        std::cout << "healed, health is now " << health << std::endl;
        healDelta = healCooldown;
    }
}


void Player::Die() 
{
    //DEATH ANIMATION HERE IF I GET THERE
    std::cout << "player instance died" << std::endl;
    isDead = true;
}

//getters
int Player::getHealth() { return health; }
int Player::getHealthMax() { return healthMax; }
float Player::getDashDelta() { return dashDelta; }
float Player::getDashCooldown() { return dashCooldown; }
bool Player::getDashing() { return isDashing; }

//draw func
void Player::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(hitBox);
}