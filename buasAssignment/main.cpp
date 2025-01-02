#define NOMINMAX
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>
#include "Classes/Objects/Player.h"
#include "Classes/Objects/Enemy.h"
#include "Classes/Mechanics/EnemyController.h"
#include "Classes/Mechanics/Ui.h"



bool gameRunning = false;

int main()
{

    //[DEBUG]  |  uncomment those 2 lines when building to release, they hide console
    //HWND hWnd = GetConsoleWindow();
    //ShowWindow(hWnd, SW_HIDE);

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
    
    window.setFramerateLimit(60);
    //===============INITIALIZE===============
    
    std::cout << "Initalizing program..." << std::endl;
    std::cout << "viewport resolution is: " << window.getSize().x << "x" << window.getSize().y << std::endl;
    std::cout << "display resolution is: " << displayResolution.width << "x" << displayResolution.height << std::endl;
    std::cout << "game resolution is: " << resolution.x << "x" << resolution.y << std::endl;

    //==================LOAD==================

    Player player = Player(resolution);
    EnemyController controller = EnemyController();
    Ui ui = Ui();

    sf::Clock clock;

    //increases spawnrate at specific intervals
    sf::Clock difficultyClock;

    //==================LOAD==================

    //main game loop
    while (window.isOpen()) 
    {
    //================UPDATE==================
    
        //DELTATIME
        sf::Time deltaTimeTimer = clock.restart();
        float delta = deltaTimeTimer.asMilliseconds();
        
        //mouse coords
        sf::Vector2i mousePos = sf::Mouse::getPosition();

        sf::Event event;
        //event loop
        while (window.pollEvent(event)) 
        {
         
   
            //action switch
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                //quit on esc
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;

            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }

        }

        //Ui update
        ui.Update(player.getHealth(), player.getHealthMax(), player.getDashDelta(), player.getDashCooldown());




        //INGAME
        if (gameRunning) 
        {
        //dash vector calculations
            // get window position
            sf::Vector2i windowPos = window.getPosition();

            // mouse position relative to window
            sf::Vector2i mousePosWindow = mousePos - windowPos;

            // res scaling (needed to calculate player position)
            sf::Vector2u windowSize = window.getSize();
            float scaleX = 1920.0f / static_cast<float>(windowSize.x);
            float scaleY = 1080.0f / static_cast<float>(windowSize.y); 

            // scale mouse pos to ingame resolution (required for windowed mode, since window is 720p, but game is 1080p)
            sf::Vector2f mousePosGame(
                mousePosWindow.x * scaleX,
                mousePosWindow.y * scaleY
            );

            //final dash vector
            sf::Vector2f dashDir(mousePosGame - player.sprite.getPosition());
        //
        
            //stops player, enemies and timers if player is dead (for animation)
            if (!player.dead) {

                //player movement
                sf::Vector2f playerMovement = player.Move(delta, dashDir);

                //enemy movements
                for (Enemy& enemy : controller.enemies) {
                    enemy.Update(player.sprite.getPosition(), delta, playerMovement);
                }
            
                //Cooldowns
                controller.TimerTick(delta, player.sprite.getPosition(), resolution);
                player.HealTick(delta);

                //increase spawnrate at 1 minute intervals
                if (difficultyClock.getElapsedTime().asSeconds() > 60 && controller.spawnTimer != 3000.0f) {
                    controller.spawnTimer -= 1000.0f;
                    difficultyClock.restart();
                }
            }
            

        }
        //================UPDATE===================
        
        
        
        //=================DRAW====================



        window.clear(sf::Color::Color(30,30,30,1));


        //INGAME
        if (gameRunning) {
            //ui
            ui.Draw(window);

            //draw all enemies
            for (Enemy& enemy : controller.enemies)
                enemy.Draw(window);


            //draw player (last so z index is highest)
            player.Draw(window);
        }
        

        window.display();
        //=================DRAW====================
    }
    
    return 0;
}