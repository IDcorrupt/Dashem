#ifndef UI_H
#define UI_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Ui {
private:
	//values
	float endFade = 0;
	bool gameRunning = true;

	//components
	sf::RectangleShape healthBar;
	sf::RectangleShape healthTracker;
	sf::RectangleShape dashBar;
	sf::RectangleShape dashTracker;
	
	sf::Font font;
	sf::Text timer;
	sf::Text score;
	sf::Text gameOver;
	sf::Text timerEnd;
	sf::Text scoreEnd;
	sf::RectangleShape shade;
	sf::Text exit;

public:
	//functions
	Ui(sf::Vector2f resolution);
	void Update(float health, float healthMax, float dashDelta, float dashCooldown, float timer, int score);
	void Draw(sf::RenderWindow& window);
	void EndScreen(float delta);
};

#endif
