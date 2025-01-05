#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Projectile.h"

class Player;


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
    int health;
    int damage;
    float speed;
    float attackCooldown;
    float attackDelta = 0;
    bool isHurt = false;
    int textureWidth;
    int textureHeight;
    bool isDying = false;       //connector between alive and "isDead" -> for death animation

    //stuff for shooter type
    int shootAmount = 4;
    int bulletsRemaining = 0;
    float shootCooldown = 1000.0f;
    float shootDelta = 0;
    
    //components
    EnemyType type;
    sf::Clock hurtTimer;
    sf::Vector2f hurtVelocity;
    sf::Vector2f attackVelocity;
    std::shared_ptr<sf::Texture> projTexture;
    sf::IntRect textureRect;
    sf::Clock animClock;
public:
    //values
    bool isDead = false;
    bool isAttacking = false;
    
    //components
    sf::Sprite sprite;
    std::vector<Projectile> projectiles; //for shooter type



public:
    //functions
    Enemy(EnemyType spawntype, const sf::Texture& Textures, std::shared_ptr<sf::Texture> projTexture);
    void Update(sf::Vector2f target, float delta, sf::Vector2f playerDisplacement, Player& player, std::vector<Enemy> otherEnemies);
    void Damaged(sf::Sprite initilaizer);
    void Die();
    void Draw(sf::RenderWindow& window);
    void CancelAttack();

    //getters
    int getHealth();
    bool getHurt();
    EnemyType getType();
    //attack types
    void NormalAttack(sf::Vector2f target);
    void ShooterAttack(sf::Vector2f target, float delta);
    void EliteAttack(sf::Vector2f target);

 
};

#endif 