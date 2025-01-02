#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <iostream>

//[CUT]

class Menu {
public:
	sf::RectangleShape startButton;
	sf::RectangleShape endButton;
	sf::RectangleShape quitButton;
	sf::Text startText;
	sf::Text endText;
	sf::Text quitText;
	bool visibility;

	Menu();
	void Mode(bool menuMode);
	void Toggle(bool mainMenu);
	void Start();
	void End();
	void Quit();
};
#endif