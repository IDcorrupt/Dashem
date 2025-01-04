#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Enemy;

class Player {
private:
    //values
    int healthMax = 5;
    int health = healthMax;
    float speed = 0.2f;
    float healCooldown = 10000.0f;  //value
    float healDelta = 0;            //counter
    float dashCooldown = 1000.0f;   //value
    float dashDelta = 0;            //counter
    int textureWidth;
    int textureHeight;
    bool isDying = false;       //connector between alive and "isDead" -> for death animation

    //components
    sf::Vector2f dashVelocity = sf::Vector2f(0, 0);
    sf::Vector2f hurtVelocity = sf::Vector2f(0, 0);
    sf::Clock hurtTimer;
    sf::Texture Texture;
    sf::IntRect textureRect;
    sf::Clock animClock;

public:
    //values
    bool isDead = false;
    bool isDashing = false;     //attack
    bool isHurt = false;

    //components
    sf::Sprite sprite;

public:
    //functions
    Player(sf::Vector2f gameRes);
    sf::Vector2f Update(float delta, sf::Vector2f dashDir, std::vector<Enemy> enemies);
    void Damaged(sf::Sprite initilaizer, bool isProjectile);
    void HealTick(float delta);
    void Draw(sf::RenderWindow& window);

    //getters
    int getHealth();
    int getHealthMax();
    float getDashDelta();
    float getDashCooldown();
    bool getDashing();

};

#endif