#include "Ui.h"
#include <filesystem>
#include <iomanip>
#include <cassert>
#include <sstream>

Ui::Ui(sf::Vector2f resolution) {
	//set appearance & position of health- & dashbars
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

	//score and timer
	if (font.loadFromFile("Assets/Roboto-Black.ttf"))
		std::cout << "Font loaded successfully..." << std::endl;
	else
		std::cout << "Font failed to load..." << std::endl;

	timer.setCharacterSize(32);
	timer.setFont(font);
	timer.setFillColor(sf::Color::White);
	timer.setString("Time:  0.00");
	timer.setPosition(sf::Vector2f(resolution.x - 200, 25));

	score.setCharacterSize(32);
	score.setFont(font);
	score.setFillColor(sf::Color::White);
	score.setString("Score:  0");
	score.setPosition(sf::Vector2f(resolution.x - 200, timer.getPosition().y + timer.getGlobalBounds().height + 20));

	//endScreen
	gameOver.setCharacterSize(64);
	gameOver.setFont(font);
	gameOver.setFillColor(sf::Color::White);
	gameOver.setString("Game Over");
	gameOver.setOrigin(sf::Vector2f(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height));
	gameOver.setPosition(sf::Vector2f(resolution.x / 2, 300));

	timerEnd.setCharacterSize(30);
	timerEnd.setFont(font);
	timerEnd.setString("Timer: 00.00");
	timerEnd.setFillColor(sf::Color::Color(255, 255, 255, 0));
	timerEnd.setOrigin(sf::Vector2f(timerEnd.getGlobalBounds().width / 2, timerEnd.getGlobalBounds().height));
	timerEnd.setPosition(sf::Vector2f(resolution.x / 2, gameOver.getGlobalBounds().top + 100));


	scoreEnd.setCharacterSize(30);
	scoreEnd.setFont(font);
	scoreEnd.setString("Score: 0");
	scoreEnd.setFillColor(sf::Color::Color(255, 255, 255, 0));
	scoreEnd.setOrigin(sf::Vector2f(scoreEnd.getGlobalBounds().width / 2, scoreEnd.getGlobalBounds().height));
	scoreEnd.setPosition(sf::Vector2f(resolution.x / 2, timerEnd.getGlobalBounds().top + 50));

	exit.setCharacterSize(40);
	exit.setFont(font);
	exit.setString("Press ESCAPE to exit the game");
	exit.setFillColor(sf::Color::Color(255, 255, 255, 0));
	exit.setOrigin(sf::Vector2f(exit.getGlobalBounds().width / 2, exit.getGlobalBounds().height));
	exit.setPosition(sf::Vector2f(resolution.x / 2, scoreEnd.getGlobalBounds().top + 150));

	shade.setSize(resolution);
	shade.setPosition(0, 0);
	shade.setFillColor(sf::Color::Color(255, 255, 255, 0));
}

void Ui::Update(float health, float healthMax, float dashDelta, float dashCooldown, float timer, int score) {
	//get percentages
	float healthRatio = health / healthMax;
	float dashRatio = dashDelta / dashCooldown;

	//calculate fill level
	float healthFill = 500 * healthRatio;
	float dashFill = 500 * dashRatio;

	//update bar fill parts
	healthTracker.setSize(sf::Vector2f(healthFill, healthTracker.getSize().y));
	dashTracker.setSize(sf::Vector2f(dashFill, dashTracker.getSize().y));

	//timer
	std::ostringstream stringstream;
	stringstream << std::fixed << std::setprecision(2) << timer;
	Ui::timer.setString("Time:  " + stringstream.str());

	//score
	Ui::score.setString("Score:  " + std::to_string(score));

}

void Ui::EndScreen(float delta)
{
	if (gameRunning) {
		gameRunning = false;
		timerEnd.setString(timer.getString());
		scoreEnd.setString(score.getString());
	}
	
	if (endFade < 253) {
		endFade += 2;
		timerEnd.setFillColor(sf::Color::Color(255, 255, 255, endFade));
		scoreEnd.setFillColor(sf::Color::Color(255, 255, 255, endFade));
		gameOver.setFillColor(sf::Color::Color(255, 255, 255, endFade));
		exit.setFillColor(sf::Color::Color(255, 255, 255, endFade));
		shade.setFillColor(sf::Color::Color(10, 10, 10, endFade / 7));
	}
}

//draw func
void Ui::Draw(sf::RenderWindow& window) {
	if (gameRunning) {
		window.draw(healthBar);
		window.draw(dashBar);
		window.draw(healthTracker);
		window.draw(dashTracker);
		window.draw(timer);
		window.draw(score);
	}
	else {
		window.draw(gameOver);
		window.draw(timerEnd);
		window.draw(scoreEnd);
		window.draw(shade);
		window.draw(exit);
	}
}


