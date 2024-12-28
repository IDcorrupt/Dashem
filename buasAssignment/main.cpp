#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>
#include "Player.h"
#include "Enemy.h"
#include "EnemyController.h"




bool gameRunning = false;

//class EnemyController {
//    //values and components
//private:
//    int eliteCounter = 0;
//public:
//    float spawnTimer;
//    float spawnCooldown;
//    std::vector<Enemy> enemies;
//    sf::Texture Textures;
//
//    //functions
//    EnemyController(float spawnTimer = 10000.0f) {
//        EnemyController::spawnTimer = spawnTimer;
//        EnemyController::spawnCooldown = 0;
//        if (Textures.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Enemies/No Outlines/enemies_x1.png"))
//            std::cout << "Enemy textures loaded successfully..." << std::endl;
//        else
//            std::cout << "Enemy textures failed to load" << std::endl;
//        
//        std::cout << "controller initialized" << std::endl;
//    }
//
//    //need windowsize for viewport -> spawning enemies out of view
//    void Spawn(sf::Vector2f playerpos, sf::Vector2f gameResolution) {
//        
//        sf::Vector2f spawnvector;
//        //convert res values to int because floats break rand()
//        int resX = gameResolution.x;
//        int resY = gameResolution.y;
//        //determine spawn location 
//        switch (rand() % 4)
//        {
//        case 0:
//            //top
//            spawnvector = sf::Vector2f(rand() % resX + 1, -50);
//            break;
//
//        case 1:
//            //left
//            spawnvector = sf::Vector2f(-50, rand() % resY + 1);
//            break;
//
//        case 2:
//            //bottom
//            spawnvector = sf::Vector2f(rand() % resX + 1, resY + 50);
//            break;
//
//        case 3:
//            //right
//            spawnvector = sf::Vector2f(resX + 50, rand() % resY + 1);
//            break;
//        default:
//            std::cout << "how. (pt2)" << std::endl;
//            break;
//        }
//        
//        //actual spawning
//        std::cout << "spawning enemy" << std::endl;
//        if (eliteCounter == 5) {
//            //spawn elite
//            std::cout << "elite spawned, resetting counter: " << std::endl;
//            enemies.push_back(Enemy(Enemy::EnemyType::Elite, Textures));
//            spawnCooldown = spawnTimer;
//            eliteCounter = 0;
//        }
//        else {
//            //spawn normal enemy
//            if (rand() % 2 == 0) {
//                std::cout << "spawning Normal, counter is at " << std::endl;
//                enemies.push_back(Enemy(Enemy::EnemyType::Normal, Textures));
//                spawnCooldown = spawnTimer;
//            }
//            else {
//                //shooter
//                std::cout << "spawning shooter, counter is at" << std::endl;
//                enemies.push_back(Enemy(Enemy::EnemyType::Shooter, Textures));
//                spawnCooldown = spawnTimer;
//            }
//            eliteCounter++; 
//            std::cout << eliteCounter << std::endl;
//        }
//
//        //set position
//        enemies[enemies.size() - 1].Sprite.setPosition(spawnvector);
//    }
//    void TimerTick(float delta, sf::Vector2f playerpos, sf::Vector2f gameResolution) {
//        if (spawnCooldown > 0)
//            spawnCooldown -= delta;
//        else
//            Spawn(playerpos, gameResolution);
//    }
//};



int main()
{
    //[SELF NOTE]  |  REMOVE AFTER ADDING MENU PLZ TY
    gameRunning = true;
       
    
    //===============INITIALIZE===============
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    //window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Dashem", sf::Style::Close, settings);
    window.setSize(sf::Vector2u(1280, 720));
    //store window resolution
    sf::Vector2f resolution = window.getView().getSize();
    //get current display's resolution
    sf::VideoMode displayResolution = sf::VideoMode::getDesktopMode();
    
    //set window position (so it looks centered)
    window.setPosition(sf::Vector2i((displayResolution.width - window.getSize().x) / 2, (displayResolution.height - window.getSize().y) / 2));
    
    window.setFramerateLimit(144);
    //===============INITIALIZE===============
    
    std::cout << "Initalizing program..." << std::endl;
    std::cout << "viewport resolution is: " << window.getSize().x << "x" << window.getSize().y << std::endl;
    std::cout << "display resolution is: " << displayResolution.width << "x" << displayResolution.height << std::endl;
    std::cout << "game resolution is: " << resolution.x << "x" << resolution.y << std::endl;

    //==================LOAD==================
    Player player = Player();
    EnemyController controller = EnemyController();
    player.Sprite.setPosition(resolution.x/2, resolution.y/2);


    //==================LOAD==================
    bool fullScreen = false;
    sf::Clock clock;

    //main game loop
    while (window.isOpen()) 
    {
    //================UPDATE==================
        //DELTATIME
        sf::Time deltaTimeTimer = clock.restart();
        float delta = deltaTimeTimer.asMilliseconds();
        //std::cout << deltaTimer.asMilliseconds() << std::endl;


        bool windowFocus = window.hasFocus();
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
                    return 0;   //[TEMP]  |  CLOSES GAME
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
                //fullscreen toggle
                else if (event.key.code == sf::Keyboard::F11) {
                    //closing current window
                    window.close();



                    //reopening window according to new viewmode
                    if (!fullScreen) {
                        window.create(sf::VideoMode(1920, 1080), "Dashem", sf::Style::Fullscreen, settings);
                        resolution = window.getView().getSize();
                        fullScreen = true;
                    }
                    else if (fullScreen) {
                        window.create(sf::VideoMode(1920, 1080), "Dashem", sf::Style::Close, settings);
                        window.setSize(sf::Vector2u(1280, 720));
                        window.setPosition(sf::Vector2i((displayResolution.width-window.getSize().x) /2, (displayResolution.height - window.getSize().y) / 2));
                        resolution = window.getView().getSize();
                        fullScreen = false;
                    }
                }
                break;

            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }

        }
        //pause game when not in focus
        if (windowFocus)
            gameRunning = true;
        else
            gameRunning = false;
        




        //INGAME
        if (gameRunning) 
        {
            //player movement
            sf::Vector2f playerMovement = player.Move(delta);
            
            //enemy movements
            for (Enemy& enemy : controller.enemies) {

                enemy.Move(player.Sprite.getPosition(), delta);
                //apply player movement
                enemy.Sprite.setPosition(enemy.Sprite.getPosition() + playerMovement);
            }
            

            //Cooldowns
            controller.TimerTick(delta, player.Sprite.getPosition(), resolution);
            
            

        }
        //================UPDATE===================
        
        
        
        //=================DRAW====================
        window.clear(sf::Color::Color(30,30,30,1));

        //draw all enemies
        for (Enemy& enemy : controller.enemies)
        {
            window.draw(enemy.Sprite);
            //[TBD]  |  if enemy is shooter, draw all of its projectiles
        }



        //draw player (last so z index is highest)
        window.draw(player.Sprite);

        window.display();
        //=================DRAW====================
    }
    
    return 0;
}