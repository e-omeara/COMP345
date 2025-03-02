#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "TowerSimulator.h"
#include "TowerObserver.h"
#include "Towers.h"





TowerSimulator::TowerSimulator(TowerObserver* towerObserver, Towers* towers){
    tObserver = towerObserver;
    tower = towers;
}


int TowerSimulator::createWindow(){

    //std::cout << "hello world";
    sf::Font font("Arial Unicode.ttf");
    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    string textstr = "Welcome to Our Tower Defense Game!\n View Towers \n Upgrade Towers";
    text.setString(textstr);

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    int mouseX;
    int mouseY;





    window = sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
               { window.close();}
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                } else if (keyPressed->scancode == sf::Keyboard::Scancode::U){
                    double balance = 1000;
                    tower->levelUp(balance);
                }
                
                    
                
            }
        }

        window.clear();
        renderTowers();
        window.display();
    }

    return 0;

}

int TowerSimulator::renderTowers(){

    sf::Font font("Arial Unicode.ttf");
     // set the string to display
     string textstr = "Welcome to Our Tower View!\n Hover for stats or press U to upgrade the tower";
     sf::Text text(font); // a font is required to make a text object
     text.setString(textstr);
 
     // set the character size
     text.setCharacterSize(20); // in pixels, not points!
 
     // set the color
     text.setFillColor(sf::Color::Red);
 
     // set the text style
     text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    sf::Vector2f towerRect(10.f, 10.f);
    sf::RectangleShape towerShape(towerRect);
    towerShape.setFillColor(sf::Color::Blue);

    int posx = tObserver->getPosition().x;
    int posy = tObserver->getPosition().y;
    
    float shapex = posx * 10.f + 140.f;
    float shapey = posy * 10.f + 140.f;
    
    
    towerShape.setPosition(sf::Vector2f(shapex, shapey));


    window.draw(towerShape);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    

    if(towerShape.getGlobalBounds().contains({static_cast<float>(mousePos.x),
        static_cast<float>(mousePos.y)})) {
        string tip = "Type: " + tObserver->getType() 
        + "\nRange: " +  to_string(tObserver->getRange())
        + "\nLevel: " + to_string(tObserver->getLevel())
        + "\nPower: " + to_string(tObserver->getPower());
        sf::Text tooltip(font);
        tooltip.setCharacterSize(16);
        tooltip.setString(sf::String(tip));
        tooltip.setFillColor(sf::Color::White);
        tooltip.setOutlineColor(sf::Color::Black);
        tooltip.setOutlineThickness(2.f);
        tooltip.setPosition({shapex + 40.f, shapey - 20.f});
        window.draw(tooltip);}

    window.draw(text);

    return 0;
}


int TowerSimulator::runGame(){

    createWindow();


    return 0;
}