#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Player;

class Projectile {
private:
	//stats
	float speed = 0.5f;
	//components
	sf::Vector2f flyVector;
	std::shared_ptr<sf::Texture> texture;
public:
	sf::Sprite sprite;
	bool hit = false;
	//functions
	Projectile(std::shared_ptr<sf::Texture> tex);
	void Shoot(float delta, sf:: Vector2f playerMovement, Player& player);
	void Explode();
	void Draw(sf::RenderWindow& window);
	void setVector(sf::Vector2f target);
};

#endif 
