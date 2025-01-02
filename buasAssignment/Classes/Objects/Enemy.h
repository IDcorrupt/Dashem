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
    int damage;
    float speed;
    float attackCooldown;
    float attackDelta = 0;
    bool attacking = false;
    bool isHurt = false;
    bool dead = false;

    //stuff for shooter type
    int shootAmount = 1;
    int bulletsRemaining = 0;
    float shootCooldown = 1000.0f;
    float shootDelta = 0;


    //components
    sf::Vector2f attackVelocity;
    sf::Texture Texture;
    sf::RectangleShape hitBox;
public:
    sf::Sprite sprite;
    std::vector<Projectile> projectiles; //for shooter type

    //functions
    Enemy(EnemyType spawntype, const sf::Texture& Textures);
    void Update(sf::Vector2f target, float delta, sf::Vector2f playerDisplacement);
    void Attack(sf::Vector2f target);
    void Damaged();
    void Die();
    void Draw(sf::RenderWindow& window);

    //getters
    int getHealth();
    bool getHurt();
    
    //attack types
    void NormalAttack(sf::Vector2f target);
    void ShooterAttack(sf::Vector2f target, float delta);
    void EliteAttack(sf::Vector2f target);

};

#endif 