#include "Math.h"

sf::Vector2f Math::NormalizeVector(sf::Vector2f vector) {
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

    sf::Vector2f normalizedVector;
    normalizedVector.x = vector.x / magnitude;
    normalizedVector.y = vector.y / magnitude;
    return normalizedVector;
}

bool Math::CheckHitboxCollision(sf::FloatRect hitbox1, sf::FloatRect hitbox2)
{
    if (hitbox1.intersects(hitbox2))
        return true;
    else
        return false;
}

float Math::VectorMagnitude(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}
