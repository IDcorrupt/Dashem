#include "EnemyController.h"
#include <SFML/Graphics.hpp>
#include "../Objects/Enemy.h"


EnemyController::EnemyController(float spawnTimer) {
    EnemyController::spawnTimer = spawnTimer;
    EnemyController::spawnCooldown = 0;
    if (Textures.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Enemies/No Outlines/enemies_x1.png"))
        std::cout << "Enemy textures loaded successfully..." << std::endl;
    else
        std::cout << "Enemy textures failed to load" << std::endl;

    std::cout << "controller initialized" << std::endl;
}

void EnemyController::Spawn(sf::Vector2f playerpos, sf::Vector2f gameResolution) {

    sf::Vector2f spawnvector;
    //convert res values to int because floats break rand()
    int resX = gameResolution.x;
    int resY = gameResolution.y;
    //determine spawn location 
    switch (rand() % 4)
    {
    case 0:
        //top
        spawnvector = sf::Vector2f(rand() % resX + 1, -50);
        break;

    case 1:
        //left
        spawnvector = sf::Vector2f(-50, rand() % resY + 1);
        break;

    case 2:
        //bottom
        spawnvector = sf::Vector2f(rand() % resX + 1, resY + 50);
        break;

    case 3:
        //right
        spawnvector = sf::Vector2f(resX + 50, rand() % resY + 1);
        break;
    default:
        std::cout << "how. (pt2)" << std::endl;
        break;
    }

    //actual spawning
    std::cout << "spawning enemy" << std::endl;
    if (eliteCounter == 5) {
        //spawn elite
        std::cout << "elite spawned, resetting counter: " << std::endl;
        enemies.push_back(Enemy(Enemy::EnemyType::Elite, Textures));
        spawnCooldown = spawnTimer;
        eliteCounter = 0;
    }
    else {
        //spawn normal enemy
        if (rand() % 2 == 0) {
            std::cout << "spawning Normal, counter is at " << std::endl;
            enemies.push_back(Enemy(Enemy::EnemyType::Normal, Textures));
            spawnCooldown = spawnTimer;
        }
        else {
            //shooter
            std::cout << "spawning shooter, counter is at" << std::endl;
            enemies.push_back(Enemy(Enemy::EnemyType::Shooter, Textures));
            spawnCooldown = spawnTimer;
        }
        eliteCounter++;
        std::cout << eliteCounter << std::endl;
    }

    //set position
    enemies[enemies.size() - 1].Sprite.setPosition(spawnvector);
}


void EnemyController::TimerTick(float delta, sf::Vector2f playerpos, sf::Vector2f gameResolution) {
    if (spawnCooldown > 0)
        spawnCooldown -= delta;
    else
        Spawn(playerpos, gameResolution);
}
