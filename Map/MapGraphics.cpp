#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "MapGraphics.h"
#include "MapObserver.h"
#include "Map.h"
#include "ColorSchemeConstants.h"

using namespace ColorSchemeConstants;

//constructor with observer and map
MapGraphics::MapGraphics(MapObserver* plugin, Map* theMap){
    
    observer = plugin;
    map = theMap;
    cout << map->getHeight() << endl;
    map->printMap();
    //map->setEntrance(1,1);
    map->printMap();
    cout << map->stringMap();
    

}

//the initial loading menu
/*
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
        window.clear(BACKGROUND_COLOR);
        window.draw(text);
        window.display();
    }
    return 0;
    
}

*/

int MapGraphics::getParameters(sf::RenderWindow* window){

    int mouseX;
    int mouseY;
    sf::Font font("Arial Unicode.ttf");
    sf::Text text(font); // a font is required to make a text object
    text.setCharacterSize(24);
    text.setFillColor(ColorSchemeConstants::TEXT_COLOR);
    text.setStyle(sf::Text::Bold);
    //copying format for user input text
    sf::Text inputText = text;



    //making menu text
    sf::Text mapMakerMenuText[5] = { sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font), sf::Text(font)};
    //copying text formatting
    for (int i = 0; i <3; i++){
        mapMakerMenuText[i] = text;
    }
    mapMakerMenuText[0].setPosition(sf::Vector2f{28, static_cast<float>(window->getSize().y/6)});
    mapMakerMenuText[0].setCharacterSize(32);
    mapMakerMenuText[0].setFillColor(ColorSchemeConstants::ACCENT_COLOR);
    mapMakerMenuText[0].setString("Welcome to the Map Maker!");

    mapMakerMenuText[1].setPosition(sf::Vector2f{30, static_cast<float>(window->getSize().y/6) + 35});
    mapMakerMenuText[1].setString("Please enter your desired width");

    mapMakerMenuText[2].setPosition(sf::Vector2f{30, static_cast<float>(window->getSize().y/6) + 95}); //extra space alotted for user input
    mapMakerMenuText[2].setString("Please enter your desired height");
    
    sf::Text inputTextX = text;
    inputTextX.setPosition(sf::Vector2f{30, static_cast<float>(window->getSize().y/6) + 65});

    sf::Text inputTextY = text;
    inputTextY.setPosition(sf::Vector2f{30, static_cast<float>(window->getSize().y/6) + 125});

    
    //MapMaking Menu
    cerr << "\n\n\n\n\n\nmapmaking";
    cerr << window->isOpen();
    std::string inputStringX = "";
    std::string inputStringY = "";
    
    int mapX = 0;
    int mapY = 0;


        //asking for width and height
    /******************************************************/
    while (window->isOpen()){
        while (const std::optional event = window->pollEvent()){
            if (event->is<sf::Event::Closed>()) 
                window->close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window->close();
                    return 1;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter ){
                    if(mapX == 0 && inputStringX !=""){
                        mapX = std::stoi(inputStringX);
                    }
                    else if(mapX != 0 && inputStringY !=""){
                        mapY = std::stoi(inputStringY);
                        break;
                    }
                }
                // Check if a number key is pressed
                sf::Keyboard::Scancode key = keyPressed->scancode;
                if (key >= sf::Keyboard::Scancode::Num1 && key <= sf::Keyboard::Scancode::Num9) {
                    if(mapX == 0){
                        inputStringX += static_cast<char>('1' + (static_cast<int>(key) - static_cast<int>(sf::Keyboard::Scancode::Num1)));
                        inputTextX.setString(inputStringX);
                    }
                    if(mapX !=0){
                        inputStringY += static_cast<char>('1' + (static_cast<int>(key) - static_cast<int>(sf::Keyboard::Scancode::Num1)));
                        inputTextY.setString(inputStringY);
                    }
                } else if (key == sf::Keyboard::Scancode::Num0) {
                    if(mapX == 0){
                        inputStringX += '0';
                        inputTextX.setString(inputStringX);
                    }
                    if(mapX !=0){
                        inputStringY += '0';
                        inputTextY.setString(inputStringY);
                    }
                }
                // Handle Backspace
                else if (key == sf::Keyboard::Scancode::Backspace) {
                    if(inputStringX.length() != 0)
                        inputStringX.pop_back();
                    else if(inputStringY.length() != 0)
                        inputStringY.pop_back();
                }
            }
            
        }
        window->clear(ColorSchemeConstants::BACKGROUND_COLOR);
        window->draw(mapMakerMenuText[0]);
        window->draw(mapMakerMenuText[1]);
        window->draw(inputTextX);
        window->draw(mapMakerMenuText[2]);
        window->draw(inputTextY);
        
        window->display();
        if(mapY!=0)
            break;
    }   
    /******************************************************/

    map->resize(mapX, mapY);

        //asking for entrance coords
    /******************************************************/
    mapMakerMenuText[0].setString("Welcome to the Map Maker!");
    mapMakerMenuText[1].setString("Please enter the X coordinate of the entrance");
    mapMakerMenuText[2].setString("Please enter the Y coordinate of the entrance");

    int entranceX = -1;
    int entranceY = -1;

    //resetting input variables
    inputStringX = "";
    inputStringY = "";

    inputTextX = text;
    inputTextY = text;
    inputTextX.setPosition(sf::Vector2f{30, static_cast<float>(window->getSize().y/6) + 65});
    inputTextY.setPosition(sf::Vector2f{30, static_cast<float>(window->getSize().y/6) + 125});


    while (window->isOpen()){
        while (const std::optional event = window->pollEvent()){
            if (event->is<sf::Event::Closed>()) 
                window->close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window->close();
                    return 1;
                }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter ){
                    if(entranceX == -1 && inputStringX !=""){
                        if(std::stoi(inputStringX) >= mapX){ //out of bounds
                            inputStringX = "";
                            cerr << "\nout of bounds\n";
                        }
                        else{entranceX = std::stoi(inputStringX);}
                    }
                    else if(entranceX != -1 && inputStringY !=""){
                        if(std::stoi(inputStringY) >= mapY){ //out of bounds
                            inputStringY = "";
                            cerr << "\nout of bounds\n";
                        }
                        else{entranceY = std::stoi(inputStringY);}
                            
                        break;
                    }
                }
                // Check if a number key is pressed
                sf::Keyboard::Scancode key = keyPressed->scancode;
                if (key >= sf::Keyboard::Scancode::Num1 && key <= sf::Keyboard::Scancode::Num9) {
                    if(entranceX == -1){
                        inputStringX += static_cast<char>('1' + (static_cast<int>(key) - static_cast<int>(sf::Keyboard::Scancode::Num1)));
                        inputTextX.setString(inputStringX);
                    }
                    if(entranceX != -1){
                        inputStringY += static_cast<char>('1' + (static_cast<int>(key) - static_cast<int>(sf::Keyboard::Scancode::Num1)));
                        inputTextY.setString(inputStringY);
                    }
                } else if (key == sf::Keyboard::Scancode::Num0) {
                    if(entranceX == -1){
                        inputStringX += '0';
                        inputTextX.setString(inputStringX);
                    }
                    if(entranceX != -1){
                        inputStringY += '0';
                        inputTextY.setString(inputStringY);
                    }
                }
                // Handle Backspace
                else if (key == sf::Keyboard::Scancode::Backspace) {
                    if(inputStringX.length() != 0)
                        inputStringX.pop_back();
                    else if(inputStringY.length() != 0)
                        inputStringY.pop_back();
                }
            }
            
        }
        window->clear(ColorSchemeConstants::BACKGROUND_COLOR);
        window->draw(mapMakerMenuText[0]);
        window->draw(mapMakerMenuText[1]);
        window->draw(inputTextX);
        window->draw(mapMakerMenuText[2]);
        window->draw(inputTextY);
        
        window->display();
        if(entranceY!=-1){
            map->setEntrance(entranceX, entranceY);
            break;
        }
    }   
    /******************************************************/

    return 0;

}


int MapGraphics::mapMaking(sf::RenderWindow* window){

   
    


    int mouseX;
    int mouseY;

    sf::Font font("Arial Unicode.ttf");
    sf::Text text(font); // a font is required to make a text object

    // set the string to display and properties
    string textstr = map->stringMap();
    cout << map->stringMap();
    text.setString(textstr);
    text.setCharacterSize(24);
    text.setFillColor(TEXT_COLOR);
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
                        string saveName = getSaveName(window);
                        if(saveName.length() != 0){
                            cout << "\nmap name: " << saveName << endl;
                            map->saveMap(saveName);
                        }
                        
                        window->close();
                        return 0;
                    }
                    
                }
            }
        }

        //clear the window, update the text, and render any graphics
        window->clear(BACKGROUND_COLOR);
        string textstr = map->stringMap();
        text.setString(displayText("Make Map"));
        window->draw(text);
        renderMap(window);
        window->display();
    }
    return 0;

}

string MapGraphics::getSaveName(sf::RenderWindow* window){

    sf::Font font("Arial Unicode.ttf");
    sf::Text text(font); // user typing will apear
    sf::Text title(font); //title

    title.setString("Please enter save name");
    title.setCharacterSize(32);
    title.setFillColor(ACCENT_COLOR);
    title.setPosition({30.f, 0.f});

    // set the string to display chosen name
    string textstr = "";
    text.setString(textstr);
    text.setCharacterSize(24);
    text.setFillColor(TEXT_COLOR);
    text.setPosition({30.f, 50.f});

    while (window->isOpen())
    {
    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window->close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {window->close();
                return "";
                }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Backspace){
                if(textstr.size() >0){
                    textstr.pop_back();
                    text.setString(textstr);
                }
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter){
                if(textstr.size() > 0){
                    cout << "\nName chosen for new map" << endl;
                    return textstr;
                } else {
                    return "";
                }
            }
        }
        if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
        {
            if ((textEntered->unicode <= 57 && textEntered->unicode >= 48) || (textEntered->unicode <= 90 && textEntered->unicode >= 65)  || (textEntered->unicode <= 122 && textEntered->unicode >= 97))
            {
                textstr = textstr + static_cast<char>(textEntered->unicode);
                text.setString(textstr);
                std::cout << "ASCII character typed: " << static_cast<char>(textEntered->unicode) << std::endl;
            }
        }
    }

    // Rest of the main loop
    window->clear(BACKGROUND_COLOR);
    window->draw(title);
    window->draw(text);
    renderMap(window);
    window->display();


    }


    return "";
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

    scenery.setFillColor(PRIMARY_COLOR);
    scenery.setSize(tileSize);
    scenery.setPosition(sf::Vector2f(100.f, 100.f));

    pathTile.setFillColor(sf::Color{ 88, 57, 39});
    pathTile.setSize(tileSize);

    tower.setFillColor(sf::Color::Blue);
    tower.setSize(tileSize);

    entry.setFillColor(sf::Color::Black);
    entry.setSize(tileSize);

    upgrade.setFillColor(ACCENT_COLOR);
    upgrade.setSize(tileSize);

    fire.setFillColor(sf::Color::Red);
    fire.setSize(tileSize);

    ice.setFillColor(sf::Color::Cyan);
    ice.setSize(tileSize);

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
            else if(tilechar == 'U'){
                upgrade.setPosition(sf::Vector2f(topCorner + tilelength*i, topCorner + tilelength*j));
                theWindow->draw(upgrade);
            }
            else if(tilechar == 'I'){
                ice.setPosition(sf::Vector2f(topCorner + tilelength*i, topCorner + tilelength*j));
                theWindow->draw(ice);
            }
            else if(tilechar == 'F'){
                fire.setPosition(sf::Vector2f(topCorner + tilelength*i, topCorner + tilelength*j));
                theWindow->draw(fire);
            }
    
        }

    }



    return 0;
}




int MapGraphics::loadingMap(sf::RenderWindow *window, vector<string> mapVect){

    sf::RectangleShape titleButton;
    sf::Font font("Arial Unicode.ttf");
    sf::Text title(font);
    sf::Text mapList(font);
    title.setString("Press a number to choose a map");
    title.setCharacterSize(24);
    title.setFillColor(TEXT_COLOR);
    //title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setPosition({50.f,50.f});

    

    
    string mapString = "";

    for(int i = 0; i < mapVect.size(); i++){
        mapString.append(to_string(i));
        mapString.append(". ");
        mapString.append(mapVect[i]);
        mapString.append("\n\n");
    }

    mapList.setString(mapString);
    mapList.setCharacterSize(20);
    mapList.setFillColor(TEXT_COLOR);

    mapList.setPosition({50.f,100.f});
    
 
    window->draw(title);
    window->draw(mapList);



    return 0;
}

//
//
//
//
//
// display the loaded map
int MapGraphics::viewMap(sf::RenderWindow *window){

    
    

    sf::Font font("Arial Unicode.ttf");
    sf::Text title(font);
    sf::Text mapList(font);
    title.setString("Press Enter to Accept\nPress Backspace to Choose Another Map");
    title.setCharacterSize(24);
    title.setFillColor(TEXT_COLOR);
    //title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setPosition({20.f,20.f});



    window->draw(title);
    renderMap(window);

    return 0;

}

//
//
//
//
//
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
    //loadingmenu();
    //mapMaking();
    //placeTowers();
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



