#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy 
{
public:
    enum EnemyType
    {
        Normal,
        Shooter,
        Elite
    };
private:
    //stats
    EnemyType type;
    int health;
    int healthMax;
    int damage;
    float speed;
    bool isHurt = false;

    //components
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;


public:
    Enemy(EnemyType spawntype);
    void Move();
    void Attack();
    void Damaged();
    void Die();
    int getHealth();
    bool getHurt();
    sf::Sprite getSprite();
};

#endif 