#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Projectile {
private:
	//stats
	float speed = 0.5f;
	//components
	sf::Texture Texture;
public:
	sf::Sprite Sprite;
	//functions
	Projectile();
	void Shoot(sf::Vector2f target);
	void Explode();
};

#endif 
