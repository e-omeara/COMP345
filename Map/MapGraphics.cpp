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





    window = sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if(event->is<sf::Event::MouseButtonPressed>()){
                sf::Vector2i position = sf::Mouse::getPosition(window);
                mouseX = position.x;
                mouseY = position.y;
                textstr.append(" \n x: ");
                textstr.append(std::to_string(mouseX));
                textstr.append(" y: ");
                textstr.append(std::to_string(mouseY));
                text.setString(textstr);
            } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    {window.close();
                }
                
                    
                
            }
        }

        window.clear();
        window.draw(text);
        window.display();
    }
    return 0;
    
}


int MapGraphics::mapMaking(){

   
    


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



    window = sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");
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
        text.setString(displayText("Make Map"));
        window.draw(text);
        renderMap();
        window.display();
    }
    return 0;

}

int MapGraphics::placeTowers(){

   
    


    int mouseX;
    int mouseY;

    sf::Font font("Courier New.ttf");
    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    string textstr = map->stringMap();
    cout << map->stringMap();
    text.setString(textstr);

    // set the character size
    text.setCharacterSize(20); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);



    window = sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);

    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if(event->is<sf::Event::MouseButtonPressed>()){
                sf::Vector2i position = sf::Mouse::getPosition(window);
                mouseX = position.x;
                mouseY = position.y;
                cout << mouseX;
                cout << mouseY;
                coord towerPos = getMapPos(mouseX, mouseY);
                int ret = map->setTower(towerPos.x, towerPos.y);
                cout << ret;
                
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    {window.close();
                }
                
                    
                
            }
        }

        window.clear();
        string textstr = map->stringMap();
        //cout << map->stringMap();
        text.setString(displayText("Play game"));
        
        window.draw(text);
        renderMap();
        window.display();
    }
    return 0;

}


string MapGraphics::displayText(string title){

    string displaystr;
    displaystr.append(title);
    displaystr.append("\n");
    displaystr.append(observer->getMessage());
    displaystr.append("\n\n");
    //displaystr.append(map->stringMap());

    return displaystr;

}

int MapGraphics::renderMap(){

    vector<char> map = observer->getMap();
    int height = observer->getHeight();
    int width = observer->getWidth();

    tilelength = 20.f;
    sf::Vector2f tileSize(tilelength, tilelength);

    scenery.setFillColor(sf::Color::Green);
    scenery.setSize(tileSize);
    scenery.setPosition(sf::Vector2f(100.f, 100.f));

    pathTile.setFillColor(sf::Color{ 88, 57, 39});
    pathTile.setSize(tileSize);

    tower.setFillColor(sf::Color::Blue);
    tower.setSize(tileSize);

    entry.setFillColor(sf::Color::Black);
    entry.setSize(tileSize);

    exit.setFillColor(sf::Color::White);
    exit.setSize(tileSize);

    

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            char tilechar = map[j*width + i];
            if(tilechar == '-'){
                scenery.setPosition(sf::Vector2f(100.f + tilelength*i, 100.f + tilelength*j));
                window.draw(scenery);
            }else if(tilechar == 'P'){
                pathTile.setPosition(sf::Vector2f(100.f + tilelength*i, 100.f + tilelength*j));
                window.draw(pathTile);
            }
            else if(tilechar == 'N'){
                entry.setPosition(sf::Vector2f(100.f + tilelength*i, 100.f + tilelength*j));
                window.draw(entry);
            }
            else if(tilechar == 'X'){
                exit.setPosition(sf::Vector2f(100.f + tilelength*i, 100.f + tilelength*j));
                window.draw(exit);
            }
            else if(tilechar == 'T'){
                tower.setPosition(sf::Vector2f(100.f + tilelength*i, 100.f + tilelength*j));
                window.draw(tower);
            }
    
        }

    }



    return 0;
}


coord MapGraphics::getMapPos(int x, int y){
    coord mapPos;
    mapPos.x = (x - 100) / tilelength;
    mapPos.y = (y - 100) / tilelength;

    cout << mapPos.x;
    cout << mapPos.y;

    return mapPos;
}




int MapGraphics::runGame(){
    loadingmenu();
    mapMaking();
    placeTowers();
    return 0;
}

int mainfunc() {

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