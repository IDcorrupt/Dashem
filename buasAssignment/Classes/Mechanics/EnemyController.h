#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H
#include <SFML/Graphics.hpp>
#include "../Objects/Enemy.h"

class EnemyController 
{
	//values and components
	private:
		int eliteCounter = 0;
	public:
		float spawnTimer;
		float spawnCooldown;
		std::vector<Enemy> enemies;
		sf::Texture Textures;
		std::shared_ptr<sf::Texture> projTexture;
		//functions
		EnemyController(float spawnTimer = 10000.0f);
		void Spawn(sf::Vector2f playerpos, sf::Vector2f gameResolution);
		void Update(float delta, sf::Vector2f playerpos, sf::Vector2f gameResolution, int& score);



};



#endif
