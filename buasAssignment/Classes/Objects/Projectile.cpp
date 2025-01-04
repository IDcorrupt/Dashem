#include "Projectile.h"
#include "../Mechanics/Math.h"
#include "player.h"
//constructor
Projectile::Projectile(std::shared_ptr<sf::Texture> tex) : texture(tex){

	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 2*32, 32, 32));
	sprite.setScale(3, 3);
	sprite.setOrigin(17, 17);
	}
void Projectile::Shoot(float delta, sf::Vector2f playerMovement, Player& player) {
	sprite.setPosition(sprite.getPosition() + flyVector * speed * delta + playerMovement);
	if (Math::CheckHitboxCollision(player.sprite.getGlobalBounds(), sprite.getGlobalBounds()) && !player.isDashing) {
		player.Damaged(sprite, true);
		Explode();
	}
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

