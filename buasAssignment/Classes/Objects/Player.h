#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
private:
    //values
    int healthMax = 5;
    int health = healthMax;
    float speed = 0.2f;
    bool dashing = false;           //attack
    float healCooldown = 10000.0f;  //value
    float healDelta = 0;            //counter
    float dashCooldown = 1000.0f;   //value
    float dashDelta = 0;            //counter
    sf::Vector2f dashVelocity = sf::Vector2f(0,0);
    sf::Texture Texture;
    sf::RectangleShape hitBox;

public:
    sf::Sprite sprite;
    bool dead = false;

    //functions
    Player(sf::Vector2f gameRes);
    sf::Vector2f Move(float delta, sf::Vector2f dashDir);
    void Damaged();
    void HealTick(float delta);
    void Die();
    int getHealth();
    int getHealthMax();
    float getDashDelta();
    float getDashCooldown();
    bool getDashing();

    void Draw(sf::RenderWindow& window);
};

#endif