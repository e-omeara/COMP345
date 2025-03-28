#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "MainMenu.h"
#include "MapObserver.h"


//the initial loading menu
int MainMenu::showMenu()
{
    // rendering window
    window = sf::RenderWindow(sf::VideoMode({800, 600}), "SFML works!");

    // loading font
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


string MainMenu::displayText(string title){
    //sets the title text

    string displaystr;
    displaystr.append(title);
    displaystr.append("\n\n");
    

    return displaystr;

}

//function to run tests
int mainfunc() {


    return 0;
}



/*

clang++ -std=c++20 -c MapObserver.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
clang++ -std=c++20 -c MapGraphics.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
clang++ -std=c++20 -c Map.cpp -I/opt/homebrew/Cellar/sfml/3.0.0_1/include;
g++ MapGraphics.o MapObserver.o Map.o -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib -lsfml-graphics -lsfml-window -lsfml-system -o myapp;
./myapp

*/