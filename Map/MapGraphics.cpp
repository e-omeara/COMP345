#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "MapGraphics.h"
#include "MapObserver.h"
#include "Map.h"

//constructor with observer and map
MapGraphics::MapGraphics(MapObserver* plugin, Map* theMap){
    
    observer = plugin;
    map = theMap;
    cout << map->getHeight() << endl;
    map->printMap();
    map->setEntrance(1,1);
    map->printMap();
    cout << map->stringMap();
    

}

//the initial loading menu
int MapGraphics::loadingmenu()
{
   
    sf::Font font("Arial Unicode.ttf");
    sf::Text text(font); // a font is required to make a text object

    // set the string to display
    string textstr = "Welcome to Our Tower Defense Game!\n Make Map \n Load Map";
    text.setString(textstr);

    // set the character size
    text.setCharacterSize(24); 

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    int mouseX;
    int mouseY;




    //create the render window
    window = sf::RenderWindow(sf::VideoMode({600, 400}), "SFML works!");
    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            //check for key inputs
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

        //clear and redraw the frame with updated text
        window.clear();
        window.draw(text);
        window.display();
    }
    return 0;
    
}


int MapGraphics::mapMaking(sf::RenderWindow* window){

   
    


    int mouseX;
    int mouseY;

    sf::Font font("Courier New.ttf");
    sf::Text text(font); // a font is required to make a text object

    // set the string to display and properties
    string textstr = map->stringMap();
    cout << map->stringMap();
    text.setString(textstr);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    //create the render window
    //window = sf::RenderWindow(sf::VideoMode({600, 400}), "Make Map!");

    

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {

            if (event->is<sf::Event::Closed>())
               { window->close();}
            else if(event->is<sf::Event::MouseButtonPressed>()){
                sf::Vector2i position = sf::Mouse::getPosition();
                mouseX = position.x;
                mouseY = position.y;
            }
            //user selects the direction in which to lay the path or chooses to exit
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window->close();
                    return 1;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Down){
                    map->laypath('d');
                    //cout << "down";
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up){
                    map->laypath('u');
                    //cout << "up";
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Left){
                    map->laypath('l');
                    //cout << "left";
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Right){
                    map->laypath('r');
                    //cout << "right";
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::E || keyPressed->scancode == sf::Keyboard::Scancode::Enter){
                    //user is trying to place the exit... validate map
                    int valid = map->setExit(); 
                    if(valid == 0){
                        window->close();
                        return 0;
                    }
                    
                }
            }
        }

        //clear the window, update the text, and render any graphics
        window->clear();
        string textstr = map->stringMap();
        text.setString(displayText("Make Map"));
        window->draw(text);
        renderMap(window);
        window->display();
    }
    return 0;

}

int MapGraphics::placeTowers(){
    //map view where the user can place towers

   
    


    int mouseX;
    int mouseY;

    sf::Font font("Courier New.ttf");
    sf::Text text(font);

    // set the string to display and properties
    string textstr = map->stringMap();
    cout << map->stringMap();
    text.setString(textstr);
    text.setCharacterSize(20); 
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    //create the renderwindow
    window = sf::RenderWindow(sf::VideoMode({600, 400}), "Place Towers!");
    
    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if(event->is<sf::Event::MouseButtonPressed>()){
                //get the mouse click coordinates
                sf::Vector2i position = sf::Mouse::getPosition(window);
                mouseX = position.x;
                mouseY = position.y;
                cout << mouseX;
                cout << mouseY;
                coord towerPos = getMapPos(mouseX, mouseY);
                //try to set a tower there
                int ret = map->setTower(towerPos.x, towerPos.y);
                cout << ret;
                
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    //user pressed the escape button
                    {window.close();
                }
                
                    
                
            }
        }

        //clear and render anew the window
        window.clear();
        string textstr = map->stringMap();
        text.setString(displayText("Play game"));
        
        window.draw(text);
        renderMap(&window);
        window.display();
    }
    return 0;

}


string MapGraphics::displayText(string title){
    //sets the map message into the title text

    string displaystr;
    displaystr.append(title);
    displaystr.append("\n");
    displaystr.append(observer->getMessage());
    displaystr.append("\n\n");
    

    return displaystr;

}

//renders the map tiles with path and tower info
int MapGraphics::renderMap(sf::RenderWindow* theWindow){

    vector<char> map = observer->getMap();
    int height = observer->getHeight();
    int width = observer->getWidth();

    //decide on size of each maptile
    tilelength = 20.f;
    topCorner = 100.f;
    sf::Vector2f tileSize(tilelength, tilelength);

    scenery.setFillColor(sf::Color::Green);
    scenery.setSize(tileSize);
    scenery.setPosition(sf::Vector2f(100.f, 100.f));

    pathTile.setFillColor(sf::Color{ 88, 57, 39});
    pathTile.setSize(tileSize);

    tower.setFillColor(sf::Color::Blue);
    tower.setSize(tileSize);
    tower.setOutlineThickness(2.f);
    tower.setOutlineColor(sf::Color::Black);

    entry.setFillColor(sf::Color::Black);
    entry.setSize(tileSize);

    exit.setFillColor(sf::Color::White);
    exit.setSize(tileSize);

    
    //looping through the map vector, place the appropriate color rectangle
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            char tilechar = map[j*width + i];
            if(tilechar == '-'){
                scenery.setPosition(sf::Vector2f(topCorner + tilelength*i, topCorner + tilelength*j));
                theWindow->draw(scenery);
            }else if(tilechar == 'P'){
                pathTile.setPosition(sf::Vector2f(topCorner + tilelength*i, topCorner + tilelength*j));
                theWindow->draw(pathTile);
            }
            else if(tilechar == 'N'){
                entry.setPosition(sf::Vector2f(topCorner + tilelength*i, topCorner + tilelength*j));
                theWindow->draw(entry);
            }
            else if(tilechar == 'X'){
                exit.setPosition(sf::Vector2f(topCorner + tilelength*i, topCorner + tilelength*j));
                theWindow->draw(exit);
            }
            else if(tilechar == 'T'){
                tower.setPosition(sf::Vector2f(topCorner + tilelength*i, topCorner + tilelength*j));
                theWindow->draw(tower);
            }
    
        }

    }



    return 0;
}

//converts x and y position to the numerical value along the map vector
coord MapGraphics::getMapPos(int x, int y){
    coord mapPos;
    mapPos.x = (x - 100) / tilelength;
    mapPos.y = (y - 100) / tilelength;

    cout << mapPos.x;
    cout << mapPos.y;

    return mapPos;
}



//runs the three stages of the map GUI
int MapGraphics::runGame(){
    loadingmenu();
    //mapMaking();
    placeTowers();
    return 0;
}

//function to run tests
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