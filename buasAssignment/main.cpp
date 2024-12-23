#include <SFML/Graphics.hpp>
#include <iostream>


bool gameRunning = false;


class Player {
private:
    //stats
    int healthMax = 5;
    int health = healthMax;
    float speed = 100.0f;
    bool dashing = false;
    float healCooldown = 10.0f;

    //components
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    //player healing
    void Heal() {
        if (health < healthMax) {
            health++;
            std::cout << "health restored, health is now " << health << std::endl;
        }
        else {
            std::cout << "health is maxed" << std::endl;
        }
        healCooldown = 2;
    }
public:
    //constructor
    Player() {
        
        if (playerTexture.loadFromFile("Assets/TECH_DUNGEON_ROUGELITE/Players/No_Outline/player_blue_x1.png"))
        {
            std::cout << "player texture set successfully..." << std::endl;
            playerSprite.setTexture(playerTexture);
            playerSprite.scale(sf::Vector2f(3, 3));
            //selecting sprite from loaded spritesheet
            int XIndex = 0;
            int YIndex = 0;
            playerSprite.setTextureRect(sf::IntRect(XIndex * 32, YIndex * 32, 32, 32));
        }
        else {
            std::cout << "player texture failed to load..." << std::endl;
        }
    }
    //player movement
    void Move() {
        //get inputs & record displacement
        sf::Vector2f displacement;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
            displacement += sf::Vector2f(0, -0.2);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            displacement += sf::Vector2f(-0.2, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
            displacement += sf::Vector2f(0, 0.2);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            displacement += sf::Vector2f(0.2, 0);

        //apply movement
        playerSprite.setPosition(playerSprite.getPosition() + displacement);

    }

    //when player damaged
    void Damaged() {
        health--;
        std::cout << "player damaged, health is now " << health << std::endl;
    }

    //when player dies
    void Die() {
        gameRunning = false;
        std::cout << "player instance died" << std::endl;
    }



    //getters
    int getHealth() { return health; }
    int getHealthMax() { return healthMax; }
    bool getDashing() { return dashing; }
    sf::Sprite getSprite() { return playerSprite; }
};
class Menu {
    //start game
    void Start() {

    }
    //quit to menu
    void End(){

    }
    //quit game
    void Quit() {

    }
};


int main()
{
    //REMOVE AFTER ADDING MENU PLZ TY
    gameRunning = true;
    //REMOVE AFTER ADDING MENU PLZ TY
       
    
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
    while (window.isOpen()) {
        //================UPDATE===================
        sf::Event event;      
        //event loop
        while (window.pollEvent(event)) {
            
            //action switch
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    if (gameRunning) {
                        //OPEN MENU
                        gameRunning = false;
                    }
                    else {
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


        if (gameRunning) {


        }
        //player movement
        player.Move();

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