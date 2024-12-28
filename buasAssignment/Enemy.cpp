#include "Enemy.h"

//vector normalizer
sf::Vector2f NormalizeVector(sf::Vector2f vector) {
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    sf::Vector2f normalizedVector;
    normalizedVector.x = vector.x / magnitude;
    normalizedVector.y = vector.y / magnitude;
    return normalizedVector;
}


//constructor
Enemy::Enemy(EnemyType spawntype, const sf::Texture& Textures) {
    int xIndex = 0;
    int yIndex = 0;
    switch (spawntype)
    {
    case Normal:
        type = Normal;
        healthMax = 2;
        damage = 1;
        speed = 0.15f;
        Sprite.setTexture(Textures);
        Sprite.scale(3, 3);
        xIndex = 0;
        yIndex = 13;
        Sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        Sprite.setOrigin(16, 18);
        break;

    case Shooter:
        type = Shooter;
        healthMax = 1;
        damage = 1;
        speed = 0.1f;

        Sprite.setTexture(Textures);
        Sprite.scale(4, 4);
        xIndex = 0;
        yIndex = 0;
        Sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        Sprite.setOrigin(16, 20);
        break;

    case Elite:
        type = Elite;
        healthMax = 5;
        damage = 2;
        speed = 0.2f;

        Sprite.setTexture(Textures);
        Sprite.scale(5, 5);
        xIndex = 0;
        yIndex = 6;
        Sprite.setTextureRect(sf::IntRect(xIndex * 32, yIndex * 32, 32, 32));
        Sprite.setOrigin(16, 24);
        break;

    default:
        std::cout << "how." << std::endl;
        //[SELF NOTE]  DESPAWN ENEMY IF DEFAULT CALLED (shouldn't happen tho)
        break;
    }

}

void Enemy::Move(sf::Vector2f target, float delta)
{
    sf::Vector2f movementvector = NormalizeVector(target - this->Sprite.getPosition()) * speed;
    this->Sprite.setPosition(this->Sprite.getPosition() + movementvector *delta);
}
void Enemy::Attack(sf::Vector2f target)
{
    switch (type)
    {
    case Enemy::Normal:
        Enemy::NormalAttack();
        break;
    case Enemy::Shooter:
        Enemy::ShooterAttack(target);
        break;
    case Enemy::Elite:
        Enemy::EliteAttack();
        break;
    default:
        break;
    }
}

void Enemy::Damaged()
{

}

void Enemy::Die()
{

}

//attack types
void Enemy::NormalAttack() {

}
void Enemy::ShooterAttack(sf::Vector2f target) {
    Projectile bullet;
    projectiles.push_back(bullet);
    bullet.Sprite.setPosition(this->Sprite.getPosition());
    sf::Vector2f shootDir = target - bullet.Sprite.getPosition();
    bullet.Shoot(NormalizeVector(shootDir));
}
void Enemy::EliteAttack() {

}
//getters
int Enemy::getHealth() { return health; }
bool Enemy::getHurt() { return isHurt; }
