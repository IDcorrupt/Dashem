#include "Player.h"


sf::Vector2f NormalizedVector(sf::Vector2f vector) {
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    sf::Vector2f normalizedVector;
    normalizedVector.x = vector.x / magnitude;
    normalizedVector.y = vector.y / magnitude;
    return normalizedVector;
}


//contructor
Player::Player(int health, int healthMax, float speed, float healCooldown, float dashCooldown)
{
    Player::health = health;
    Player::healthMax = healthMax;
    Player::speed = speed;
    Player::healCooldown = healCooldown;
    Player::healDelta = 0;
    Player::dashCooldown = dashCooldown;
    Player::dashDelta = 0;
    Player::dead = false;


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
sf::Vector2f Player::Move(float delta, sf::Vector2f dashDir) 
{
    if (dashing) {

        //exit dash if slow enough
        if (std::sqrt(dashVelocity.x * dashVelocity.x + dashVelocity.y * dashVelocity.y) < 1.2) {
            dashing = false;
            dashVelocity = sf::Vector2f(0, 0);
            dashDelta = dashCooldown;
            return sf::Vector2f(0, 0);
        }

        //reduce velocity
        float reduction = speed / 3;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !dashing && !(dashDelta > 0)) {
            //initiate dash
            std::cout << "Inin" << std::endl;
            dashVelocity = NormalizedVector(dashDir) * (speed * 10);
            dashing = true;
        }
        if (dashDelta > 0)
            dashDelta -= delta;
        else
            dashDelta = 0;


        //get inputs & record displacement
        sf::Vector2f displacement;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            displacement += sf::Vector2f(0, -speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            displacement += sf::Vector2f(-speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            displacement += sf::Vector2f(0, speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            displacement += sf::Vector2f(speed, 0);
     
        //apply movement
        return -displacement * delta;
    
    }

    //sprite facing
    // [SELF NOTE]  |  negative scale didnt work -> do this later when you know how
}
void Player::HealTick(float delta) {
    if (health != healthMax && healDelta > 0)
        healDelta -= delta;
    else if(health < healthMax){
        health++;
        std::cout << "healed, health is now " << health << std::endl;
        healDelta = healCooldown;
    }
}

void Player::Damaged() 
{
    health--;
    std::cout << "player damaged, health is now " << health << std::endl;
    healDelta = healCooldown;
    if (health == 0) {
        Die();
    }
}
void Player::Die() 
{
    //DEATH ANIMATION HERE IF I GET THERE
    std::cout << "player instance died" << std::endl;
    dead = true;
}

//getters
int Player::getHealth() { return health; }
int Player::getHealthMax() { return healthMax; }
float Player::getDashDelta() { return dashDelta; }
float Player::getDashCooldown() { return dashCooldown; }
bool Player::getDashing() { return dashing; }

//draw func
void Player::Draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(hitBox);
}