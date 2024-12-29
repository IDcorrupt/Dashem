#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
private:
	bool menuMode;
	sf::RectangleShape startButton;
	sf::RectangleShape endButton;
	sf::RectangleShape quitButton;
	sf::Text startText;
	sf::Text endText;
	sf::Text quitText;
public:
	bool visibility;

	Menu();
	void Toggle(sf::Vector2u viewPort, bool mainMenu);
	void Start();
	void End();
	void Quit();
};
#endif