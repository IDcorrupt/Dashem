#include "Player.h"

//contructor
Player::Player(int health, int healthMax, float speed, float healCooldown)
{
    Player::health = health;
    Player::healthMax = healthMax;
    Player::speed = speed;
    Player::healCooldown = healCooldown;
    if (Texture.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Players/No_Outline/player_blue_x1.png"))
    {
        std::cout << "player texture set successfully..." << std::endl;
        Sprite.setTexture(Texture);
        Sprite.scale(sf::Vector2f(3, 3));
        //selecting sprite from loaded spritesheet
        int xIndex = 0;
        int yIndex = 0;
        Sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
    }
    else
    {
        std::cout << "player texture failed to load..." << std::endl;
    }
}

//functions
void Player::Move() 
{
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

    //sprite facing
    // [SELF NOTE]  |  negative scale didnt work -> do this later when you know how
    //apply movement
    Sprite.setPosition(Sprite.getPosition() + displacement);
}
void Player::Damaged() 
{
    health--;
    std::cout << "player damaged, health is now " << health << std::endl;
}
void Player::Heal() 
{
    if (health < healthMax)
    {
        health++;
        std::cout << "health restored, health is now " << health << std::endl;
    }
    else
    {
        std::cout << "health is maxed" << std::endl;
    }
    healCooldown = 2;
}
void Player::Die() 
{
    std::cout << "player instance died" << std::endl;
}

//getters
int Player::getHealth() { return health; }
int Player::getHealthMax() { return healthMax; }
bool Player::getDashing() { return dashing; }

