#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
private:
    //stats
    int healthMax = 5;
    int health = healthMax;
    float speed = 0.2f;
    bool dashing = false; //attack
    float healCooldown = 10.0f;

    //components
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

public:
    Player();
    void Move();
    void Damaged();
    void Heal();
    void Die();
    int getHealth();
    int getHealthMax();
    bool getDashing();
    sf::Sprite getSprite();
};

#endif