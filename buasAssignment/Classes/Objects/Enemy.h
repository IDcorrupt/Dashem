#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Projectile.h"

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
    sf::Texture Texture;
public:
    sf::Sprite sprite;
    std::vector<Projectile> projectiles; //for shooter type

    //functions
    Enemy(EnemyType spawntype, const sf::Texture& Textures);
    void Move(sf::Vector2f target, float delta);
    void Attack(sf::Vector2f target);
    void Damaged();
    void Die();
    void Draw(sf::RenderWindow& window);

    //getters
    int getHealth();
    bool getHurt();
    
    //attack types
    void NormalAttack();
    void ShooterAttack(sf::Vector2f target);
    void EliteAttack();

};

#endif 