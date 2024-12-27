#include "Projectile.h"

//constructor
Projectile::Projectile(){
	if (Texture.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Projectiles/projectiles_x1.png")) {
		std::cout << "Projectile texture loaded..." << std::endl;

		Sprite.setTexture(Texture);
		Sprite.setTextureRect(sf::IntRect(2, 0, 32, 32));
	}

}
void Projectile::Shoot(sf::Vector2f target) {
	Sprite.setPosition(Sprite.getPosition() + target * speed);
}

void Projectile::Explode() {
	//if touching player
}