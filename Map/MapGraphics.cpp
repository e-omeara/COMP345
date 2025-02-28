#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "MapGraphics.h"
#include "MapObserver.h"
#include "Map.h"


MapGraphics::MapGraphics(MapObserver* plugin, Map* theMap){
    //Map *map;
    observer = plugin;
    map = theMap;
    cout << map->getHeight() << endl;
    map->printMap();
    map->setEntrance(1,1);
    map->printMap();
    cout << map->stringMap();
    

}


int MapGraphics::loadingmenu()
{
    //std::cout << "hello world";
    sf::Font font("Arial Unicode.ttf");
    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    string textstr = "Welcome to Our Tower Defense Game!\n Make Map \n Load Map";
    text.setString(textstr);

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    int mouseX;
    int mouseY;





    sf::RenderWindow window(sf::VideoMode({600, 400}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if(event->is<sf::Event::MouseButtonPressed>()){
                sf::Vector2i position = sf::Mouse::getPosition();
                mouseX = position.x;
                mouseY = position.y;
                textstr.append(" \n x: ");
                textstr.append(std::to_string(mouseX));
                textstr.append(" y: ");
                textstr.append(std::to_string(mouseY));
                text.setString(textstr);
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }
    return 0;
    
}


int MapGraphics::MapMaking(){

   
    


    int mouseX;
    int mouseY;

    sf::Font font("Courier New.ttf");
    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    string textstr = map->stringMap();
    cout << map->stringMap();
    text.setString(textstr);

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);



    sf::RenderWindow window(sf::VideoMode({600, 400}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);

    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if(event->is<sf::Event::MouseButtonPressed>()){
                sf::Vector2i position = sf::Mouse::getPosition();
                mouseX = position.x;
                mouseY = position.y;
                string textstr = text.getString();
                textstr.append(" \n x: ");
                textstr.append(std::to_string(mouseX));
                textstr.append(" y: ");
                textstr.append(std::to_string(mouseY));
                text.setString(textstr);
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    {window.close();
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Down){
                    map->laypath('d');
                    //cout << "down";
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up){
                    map->laypath('u');
                    //cout << "down";
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Left){
                    map->laypath('l');
                    //cout << "down";
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Right){
                    map->laypath('r');
                    //cout << "down";
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::E){
                    int valid = map->setExit();
                    if(valid == 0){
                        window.close();
                        return 0;}
                    //cout << "down";
                }
            }
        }

        window.clear();
        string textstr = map->stringMap();
        //cout << map->stringMap();
        text.setString(displayText());
        window.draw(text);
        window.display();
    }
    return 0;

}


string MapGraphics::displayText(){

    string displaystr;
    displaystr.append("Title here!\n");
    displaystr.append(observer->getMessage());
    displaystr.append("\n\n");
    displaystr.append(map->stringMap());

    return displaystr;

}




int MapGraphics::runGame(){
    loadingmenu();
    MapMaking();
    return 0;
}

int main() {

    MapObserver* observer = new MapObserver;
    Map* map = new Map(20,10);
    cout << "hello?";
    map->getObserver(observer);
    MapGraphics graphics(observer, map);
    map->printMap();
    cout << map->stringMap();
   
    graphics.runGame();

    return 0;
}



/*

clang++ -std=c++20 -c MapObserver.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
clang++ -std=c++20 -c MapGraphics.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
clang++ -std=c++20 -c Map.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
g++ MapGraphics.o MapObserver.o Map.o -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system -o myapp;
./myapp

*/