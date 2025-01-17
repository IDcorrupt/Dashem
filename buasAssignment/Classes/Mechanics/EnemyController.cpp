#include "EnemyController.h"
#include <SFML/Graphics.hpp>
#include "../Objects/Enemy.h"


EnemyController::EnemyController(float spawnTimer) {
    EnemyController::spawnTimer = spawnTimer;
    EnemyController::spawnCooldown = 0;
    if (Textures.loadFromFile("Assets/enemies_x1.png"))
        std::cout << "Enemy textures loaded successfully..." << std::endl;
    else
        std::cout << "Enemy textures failed to load" << std::endl;

    projTexture = std::make_shared<sf::Texture>();
    if (projTexture->loadFromFile("Assets/projectiles_x1.png")) {
        std::cout << "Projectile texture loaded successfully..." << std::endl;
    }
    else {
        std::cout << "Projectile texture failed to load" << std::endl;
    }

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
    if (eliteCounter == 5) {
        //spawn elite
        enemies.push_back(Enemy(Enemy::EnemyType::Elite, Textures, projTexture));
        spawnCooldown = spawnTimer;
        eliteCounter = 0;
    }
    else {
        //spawn normal enemy
        if (rand() % 2 == 0) {
            enemies.push_back(Enemy(Enemy::EnemyType::Normal, Textures, projTexture));
            spawnCooldown = spawnTimer;
        }
        else {
            //shooter
            enemies.push_back(Enemy(Enemy::EnemyType::Shooter, Textures, projTexture));
            spawnCooldown = spawnTimer;
        }
        eliteCounter++;
    }

    //set position
    enemies[enemies.size() - 1].sprite.setPosition(spawnvector);
}


void EnemyController::Update(float delta, sf::Vector2f playerpos, sf::Vector2f gameResolution, int& score) {
    if (spawnCooldown > 0)
        spawnCooldown -= delta;
    else
        Spawn(playerpos, gameResolution);
    
    for (size_t i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].isDead) {
            switch (enemies[i].getType())
            {
            case (Enemy::Normal):
                score++;
                break;
            case (Enemy::Shooter):
                score++;
                break;
            case (Enemy::Elite):
                score += 5;
                break;
            default:
                break;
            }
            enemies.erase(enemies.begin() + i);
        }
    }
}
