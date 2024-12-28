#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>
#include "Player.h"
#include "Enemy.h"




bool gameRunning = false;

class EnemyController {
    //values and components
private:
    int eliteCounter = 0;
public:
    float spawnTimer;
    std::vector<Enemy> enemies;
    sf::Texture Textures;

    //functions
    EnemyController(float spawnTimer = 10.0f) {
        EnemyController::spawnTimer = spawnTimer;
        if (Textures.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Enemies/No Outlines/enemies_x1.png"))
            std::cout << "Enemy textures loaded successfully..." << std::endl;
        else
            std::cout << "Enemy textures failed to load" << std::endl;
        
        std::cout << "controller initialized" << std::endl;
    }

    //need windowsize for viewport -> spawning enemies out of view
    void Spawn(sf::Vector2f playerpos, sf::Vector2u windowsize) {
        if (spawnTimer <= 0) {
            std::cout << "spawning enemy" << std::endl;
            if (eliteCounter == 5) {
                //spawn elite
                std::cout << "elite spawned, resetting counter: " << std::endl;
                enemies.push_back(Enemy(Enemy::EnemyType::Elite, Textures));
                spawnTimer = 10.0f;
                eliteCounter = 0;
            }
            else {
                //spawn normal enemy
                if (rand() % 2 == 0) {
                    std::cout << "spawning Normal, counter is at " << std::endl;
                    Enemy fucker = Enemy(Enemy::EnemyType::Normal, Textures);
                    enemies.push_back(fucker);

                    spawnTimer = 10.0f;
                }
                else {
                    //shooter
                    std::cout << "spawning shooter, counter is at" << std::endl;
                    enemies.push_back(Enemy(Enemy::EnemyType::Shooter, Textures));
                    spawnTimer = 10.0f;
                }
                eliteCounter++; 
                std::cout << eliteCounter << std::endl;
            }
            //set position
            enemies[enemies.size() - 1].Sprite.setPosition(500, 0);


        }

    }
    void TimerTick() {
        //[SELF NOTE]  |  CHANGE THIS TO DELTATIME WHEN IMPLEMENTED
        spawnTimer = spawnTimer - 0.002f;
    }
};



int main()
{
    //[SELF NOTE]  |  REMOVE AFTER ADDING MENU PLZ TY
    gameRunning = true;
       
    
    //===============INITIALIZE===============
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    //window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "buasAssignment", sf::Style::Fullscreen, settings);
    //===============INITIALIZE===============
    
    std::cout << "Initalizing program, viewport resolution is: " << window.getSize().x << "x" << window.getSize().y << std::endl;
    

    //==================LOAD==================
    Player player = Player();
    EnemyController controller = EnemyController();
    player.Sprite.setPosition(1000, 600);
    //==================LOAD==================

    //main game loop
    while (window.isOpen()) 
    {
    //================UPDATE==================
        sf::Event event;      
        //event loop
        while (window.pollEvent(event)) 
        {
            
            //action switch
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) 
                {
                    return 0;   //[TEMP] CLOSES GAME
                    if (gameRunning) 
                    {
                        //OPEN MENU
                        gameRunning = false;
                    }
                    else 
                    {
                        //CLOSE MENU
                        gameRunning = true;
                    }
                }
                break;

            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::LostFocus:
                //PAUSE GAME
                break;
            default:
                break;
            }
        }


        //for pause control
        if (gameRunning) 
        {
            
            for (Enemy& enemy : controller.enemies) {
                enemy.Move(player.Sprite.getPosition());
            }
            
            if (controller.spawnTimer > 0)
                controller.TimerTick();
            
            
            //player movement
            player.Move();
                
            
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

                controller.Spawn(player.Sprite.getPosition(), window.getSize());
            }
        }
        //================UPDATE===================
        
        
        
        //=================DRAW====================
        window.clear(sf::Color::Color(30,30,30,1));

        for (Enemy& enemy : controller.enemies)
        {
            window.draw(enemy.Sprite);
        }

        //draw player (last so z index is highest)
        //window.draw(testEnemy.Sprite);
        window.draw(player.Sprite);
        window.display();
        //=================DRAW====================
    }
    
    return 0;
}