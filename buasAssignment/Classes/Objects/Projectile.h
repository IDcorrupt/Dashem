#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Projectile {
private:
	//stats
	float speed = 0.5f;
	//components
	sf::Vector2f flyVector;
	sf::Texture Texture;
public:
	sf::Sprite sprite;
	bool hit = false;
	//functions
	Projectile();
	void Shoot(float delta, sf:: Vector2f playerMovement);
	void Explode();
	void Draw(sf::RenderWindow& window);
	void setVector(sf::Vector2f target);
};

#endif 
