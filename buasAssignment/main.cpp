#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"


bool gameRunning = false;


int main()
{
    //[SELF NOTE]  |  REMOVE AFTER ADDING MENU PLZ TY
    gameRunning = true;
    //[SELF NOTE]  |  REMOVE AFTER ADDING MENU PLZ TY
       
    
    //===============INITIALIZE===============
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "buasAssignment", sf::Style::Default, settings);
    //===============INITIALIZE===============
    
    //==================LOAD==================
    Player player = Player();
    //==================LOAD==================

    //main game loop
    while (window.isOpen()) 
    {
        //================UPDATE===================
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


        if (gameRunning) 
        {
           //player movement
            player.Move();
        }

        //================UPDATE===================
        // 
        //=================DRAW====================
        window.clear(sf::Color::Black);
        window.draw(player.getSprite());
        window.display();
        //=================DRAW====================
    }
    
    return 0;
}