#include "Menu.h"

std::vector<sf::RectangleShape> buttons;
std::vector<sf::Text> texts;

Menu::Menu() {
	menuMode = false;
	visibility = false;
	buttons.push_back(startButton);
	buttons.push_back(endButton);
	buttons.push_back(quitButton);
	for (sf::RectangleShape button : buttons) {
		button.setFillColor(sf::Color::Color(0, 0, 0, 100));
		button.setSize(sf::Vector2f(300, 50));
	}
}

void Menu::Toggle(sf::Vector2u viewPort, bool menuMode) {
	if (visibility) {
		//turn off

		visibility = false;
	}
	else {
		//turn on
		if (menuMode) {
			//main menu -> no end button & start says "start"
			for (sf::RectangleShape button : buttons) {
				button.setSize(sf::Vector2f((button.getSize().x * viewPort.x)/500, (button.getSize().y * viewPort.y)/500));
			}
		}


		Menu::menuMode = menuMode;
		visibility = true;
	}
}

void Menu::Start() {

}

void Menu::End() {

}

void Menu::Quit() {

}