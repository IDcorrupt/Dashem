#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
private:
    //stats
    int healthMax;
    int health;
    float speed;
    float healCooldown;
    bool dashing = false; //attack

    //components
    sf::Texture Texture;

public:
    sf::Sprite Sprite;
    
    //functions
    Player(int health = 5, int healthMax = 5, float speed = 0.2f, float healCooldown = 10.0f);
    sf::Vector2f Move(float delta);
    void Damaged();
    void Heal();
    void Die();
    int getHealth();
    int getHealthMax();
    bool getDashing();
};

#endif