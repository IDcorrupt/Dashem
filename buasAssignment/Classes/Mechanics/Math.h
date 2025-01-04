#pragma once
#include <SFML/Graphics.hpp>
class Math
{
public:
	static sf::Vector2f NormalizeVector(sf::Vector2f vector);
	static bool CheckHitboxCollision(sf::FloatRect hitbox1, sf::FloatRect hitbox2);
	static float VectorMagnitude(sf::Vector2f vector);
};

