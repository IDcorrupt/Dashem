#include "Projectile.h"

//constructor
Projectile::Projectile(){
	if (Texture.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Projectiles/projectiles_x1.png")) {
		std::cout << "Projectile texture loaded..." << std::endl;

		sprite.setTexture(Texture);
		sprite.setTextureRect(sf::IntRect(2, 0, 32, 32));
	}

}
void Projectile::Shoot(float delta, sf::Vector2f playerMovement) {
	sprite.setPosition(sprite.getPosition() + flyVector * speed * delta + playerMovement);
	
}

void Projectile::Explode() {
	printf("exploded");
	hit = true;
}

void Projectile::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Projectile::setVector(sf::Vector2f target) { flyVector = target; }

