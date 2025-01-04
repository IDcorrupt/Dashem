#include "Projectile.h"
#include "../Mechanics/Math.h"
#include "player.h"
sf::RectangleShape asd;
//constructor
Projectile::Projectile(std::shared_ptr<sf::Texture> tex) : texture(tex){

	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 2*32, 32, 32));
	sprite.setScale(3, 3);
	sprite.setOrigin(17, 17);
	
	//hitbox
	hitBox.setSize(sf::Vector2f(19, 20));
	hitBox.setOrigin(hitBox.getSize().x / 2, hitBox.getSize().y / 2);
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineColor(sf::Color::Blue);
	hitBox.setOutlineThickness(2);
	hitBox.setPosition(sprite.getPosition());

	//test
	asd.setSize(sf::Vector2f(2, 2));
	asd.setOrigin(1, 1);
	asd.setFillColor(sf::Color::Magenta);
	asd.setOutlineThickness(0);

	}
void Projectile::Shoot(float delta, sf::Vector2f playerMovement, Player& player) {
	sprite.setPosition(sprite.getPosition() + flyVector * speed * delta + playerMovement);
	hitBox.setPosition(sprite.getPosition());
	asd.setPosition(sprite.getPosition());
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
	window.draw(hitBox);
	window.draw(asd);
}

void Projectile::setVector(sf::Vector2f target) { flyVector = target; }

