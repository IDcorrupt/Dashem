#include "Menu.h"

//[CUT]

std::vector<sf::RectangleShape> buttons;
std::vector<sf::Text> texts;

Menu::Menu() {
	visibility = false;
	buttons.push_back(startButton);
	buttons.push_back(endButton);
	buttons.push_back(quitButton);
	int i = 1;
	for (sf::RectangleShape button : buttons) {
		button.setFillColor(sf::Color::Color(0, 0, 0, 100));
		button.setSize(sf::Vector2f(300, 50));
		button.setPosition(810, 500 + (i * 70));
	}
	i = i;
	for (sf::Text text : texts) {
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(30);
	}
	startText.setString("Continue");
	endText.setString("Back");
	quitText.setString("Quit");
}

void Menu::Mode(bool menuMode) {
	if (menuMode) {
	}
}
void Menu::Toggle(bool menuMode) {
	if (visibility) {
		//turn off
		for (sf::RectangleShape button : buttons) {
			button.setScale(0, 0);
		}
		for (sf::Text text : texts) {
			text.setScale(0, 0);
		}
		visibility = false;
	}
	else {
		//turn on
		startText.setString("Continue");
		for (sf::RectangleShape button : buttons) {
			button.setScale(1, 1);
		}
		for (sf::Text text : texts) {
			text.setScale(1, 1);
		}
		quitButton.setPosition(700, 710);
		quitText.setPosition(700, 710);
		if (menuMode) {
			//main menu -> no end button & start says "start"
			startText.setString("Start");
			endText.setScale(0, 0);
			endButton.setScale(0, 0);
			quitButton.setPosition(700, 640);
			quitText.setPosition(700, 640);
		}


		visibility = true;
	}
}

void Menu::Start() {

}

void Menu::End() {

}

void Menu::Quit() {

}