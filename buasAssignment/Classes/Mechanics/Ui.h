#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Ui {
public:
	sf::RectangleShape healthBar;
	sf::RectangleShape healthTracker;
	sf::RectangleShape dashBar;
	sf::RectangleShape dashTracker;

	Ui();
	void Update(float health, float healthMax, float dashDelta, float dashCooldown);
	void Toggle(bool mode);
};

#endif
