#include "Enemy.h"

//constructor
Enemy::Enemy(EnemyType spawntype) {
    switch (spawntype)
    {
    case Normal:
        type = Normal;
        healthMax = 2;
        damage = 1;
        speed = 0.15f;
        if (enemyTexture.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Enemies/No Outlines/enemies_x1.png")) {
            std::cout << "Enemy [type normal] texture loaded..." << std::endl;
            enemySprite.setTexture(enemyTexture);
            enemySprite.scale(3, 3);
            int xIndex = 0;
            int yIndex = 13;
            enemySprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        }
        else
            std::cout << "Enemy [type normal] texture failed to load..." << std::endl;
        break;

    case Shooter:
        type = Shooter;
        healthMax = 1;
        damage = 1;
        speed = 0.1f;
        if (enemyTexture.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Enemies/No Outlines/enemies_x1.png")) {
            std::cout << "Enemy [type shooter] texture loaded..." << std::endl;
            enemySprite.setTexture(enemyTexture);
            enemySprite.scale(3, 3);
            int xIndex = 0;
            int yIndex = 0;
            enemySprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        }
        else
            std::cout << "Enemy [type shooter] texture failed to load..." << std::endl;
        break;

    case Elite:
        type = Elite;
        healthMax = 5;
        damage = 2;
        speed = 0.2f;
        if (enemyTexture.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Enemies/No Outlines/enemies_x1.png")) {
            std::cout << "Enemy [type elite] texture loaded..." << std::endl;
            enemySprite.setTexture(enemyTexture);
            enemySprite.scale(4, 4);
            int xIndex = 0;
            int yIndex = 6;
            enemySprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        }
        else
            std::cout << "Enemy [type elite] texture failed to load..." << std::endl;
        break;
    default:
        //[SELF NOTE]  DESPAWN ENEMY IF DEFAULT CALLED (shouldn't happen tho)
        break;
    }
}

void Enemy::Move()
{

}
void Enemy::Attack()
{

}
void Enemy::Damaged()
{

}
void Enemy::Die()
{

}
//getters
int Enemy::getHealth() { return health; }
bool Enemy::getHurt() { return isHurt; }
sf::Sprite Enemy::getSprite() { return enemySprite; }