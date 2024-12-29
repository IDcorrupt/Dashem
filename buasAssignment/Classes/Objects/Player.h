#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
private:
    //values
    int healthMax;
    int health;
    float speed;
    float healCooldown;     //value
    float healDelta;        //counter
    bool dashing = false;   //attack
    float dashCooldown;     //value
    float dashDelta;        //counter
    sf::Vector2f dashVelocity = sf::Vector2f(0,0);
    sf::Texture Texture;

public:
    sf::Sprite Sprite;
    bool dead;

    //functions
    Player(int health = 5, int healthMax = 5, float speed = 0.2f, float healCooldown = 10000.0f, float dashCooldown = 1000.0f);
    sf::Vector2f Move(float delta, sf::Vector2f dashDir);
    void Damaged();
    void HealTick(float delta);
    void Die();
    int getHealth();
    int getHealthMax();
    float getDashDelta();
    float getDashCooldown();
    bool getDashing();
};

#endif