#include "Ui.h"

Ui::Ui() {
	healthBar.setFillColor(sf::Color::Transparent);
	healthBar.setOutlineColor(sf::Color::Red);
	healthBar.setOutlineThickness(5);
	healthBar.setSize(sf::Vector2f(500, 30));
	healthBar.setPosition(sf::Vector2f(10, 10));
	
	dashBar.setFillColor(sf::Color::Transparent);
	dashBar.setOutlineColor(sf::Color::White);
	dashBar.setOutlineThickness(5);
	dashBar.setSize(sf::Vector2f(500, 30));
	dashBar.setPosition(sf::Vector2f(10, 60));
	dashBar.scale(0.6, 0.6);

	healthTracker.setFillColor(sf::Color::Red);
	healthTracker.setOutlineColor(sf::Color::Transparent);
	healthTracker.setOutlineThickness(5);
	healthTracker.setSize(sf::Vector2f(500, 30));
	healthTracker.setPosition(sf::Vector2f(10, 10));

	dashTracker.setFillColor(sf::Color::White);
	dashTracker.setOutlineColor(sf::Color::Transparent);
	dashTracker.setOutlineThickness(5);
	dashTracker.setSize(sf::Vector2f(500, 30));
	dashTracker.setPosition(sf::Vector2f(10, 60));
	dashTracker.scale(0.6, 0.6);
}

void Ui::Update(float health, float healthMax, float dashDelta, float dashCooldown) {
	//get percentages
	float healthRatio = health / healthMax;
	float dashRatio = dashDelta / dashCooldown;

	float healthFill = 500 * healthRatio;
	float dashFill = 500 * dashRatio;
	healthTracker.setSize(sf::Vector2f(healthFill, healthTracker.getSize().y));
	dashTracker.setSize(sf::Vector2f(dashFill, dashTracker.getSize().y));
}

void Ui::Toggle(bool mode) {

}