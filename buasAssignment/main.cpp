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
#include "Classes/Mechanics/Menu.h"
#include "Classes/Mechanics/Ui.h"



bool gameRunning = false;
bool paused = false;

int main()
{

    //[DEBUG]  |  uncomment those 2 lines when building to release, they hide console
    //HWND hWnd = GetConsoleWindow();
    //ShowWindow(hWnd, SW_HIDE);

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
    
    window.setFramerateLimit(60);
    //===============INITIALIZE===============
    
    std::cout << "Initalizing program..." << std::endl;
    std::cout << "viewport resolution is: " << window.getSize().x << "x" << window.getSize().y << std::endl;
    std::cout << "display resolution is: " << displayResolution.width << "x" << displayResolution.height << std::endl;
    std::cout << "game resolution is: " << resolution.x << "x" << resolution.y << std::endl;

    //==================LOAD==================

    Player player = Player();
    EnemyController controller = EnemyController();
    Menu menu = Menu();
    Ui ui = Ui();
    player.Sprite.setPosition(resolution.x/2, resolution.y/2);

    bool fullScreen = false;
    sf::Clock clock;

    //open menu in main menu mode
    menu.Toggle(window.getSize(), true);
    //==================LOAD==================

    //main game loop
    while (window.isOpen()) 
    {
    //================UPDATE==================
    
        //DELTATIME
        sf::Time deltaTimeTimer = clock.restart();
        float delta = deltaTimeTimer.asMilliseconds();
        sf::Vector2i mousePos = sf::Mouse::getPosition();

        // store/update window focus state
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
                    if (paused) 
                    {
                        //OPEN MENU
                        menu.Toggle(window.getSize(), false);
                        paused = true;
                    }
                    else 
                    {
                        menu.Toggle(window.getSize(), false);
                        //CLOSE MENU
                        paused = false;
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
                else if (event.key.code == sf::Keyboard::E) {
                    player.Damaged();
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
        if (!windowFocus && gameRunning && false) { //[DEBUG]  |  false added so it doesn't do anything, remove when menu works
            menu.Toggle(window.getSize(), false);
            gameRunning = false;
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
            sf::Vector2f dashDir(mousePosGame - player.Sprite.getPosition());

            //windowed mode correction
            if (!fullScreen)
                dashDir = dashDir + sf::Vector2f(-13, -60);

            //stops player, enemies and timers if player is dead (for animation)
            if (!player.dead) {

            //player movement
            sf::Vector2f playerMovement = player.Move(delta, dashDir);
            
                //enemy movements
                for (Enemy& enemy : controller.enemies) {

                    enemy.Move(player.Sprite.getPosition(), delta);
                    //apply player movement
                    enemy.Sprite.setPosition(enemy.Sprite.getPosition() + playerMovement);
                }
            
                //Cooldowns
                controller.TimerTick(delta, player.Sprite.getPosition(), resolution);
                player.HealTick(delta);
            }
         //   else
         //       gameRunning = false;
            

        }
        //================UPDATE===================
        
        
        
        //=================DRAW====================



        window.clear(sf::Color::Color(30,30,30,1));

        //menu stuff



        //INGAME
        if (gameRunning) {
            //ui
            window.draw(ui.healthBar);
            window.draw(ui.dashBar);
            window.draw(ui.healthTracker);
            window.draw(ui.dashTracker);

            //draw all enemies
            for (Enemy& enemy : controller.enemies)
            {
                window.draw(enemy.Sprite);
                //[TBD]  |  if enemy is shooter, draw all of its projectiles
            }



            //draw player (last so z index is highest)
            window.draw(player.Sprite);
        }
        

        window.display();
        //=================DRAW====================
    }
    
    return 0;
}