#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "MainMenu.h"

//constructor
MainMenu::MainMenu(float width, float height, sf::RenderWindow* window, sf::Font font) 
    : font(font) , window(window){
    if(!font.openFromFile("Arial Unicode.ttf")){
        cerr << "unable to load font from file";
        return;
    }

    menuSelected = 0;

    // Load Map
    mainMenuText[0]->setFont(font);
    mainMenuText[0]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[0]->setString("Play");
    mainMenuText[0]->setCharacterSize(70);
    mainMenuText[0]->setPosition(sf::Vector2f(width / 2, height / 6));

    // Make Map
    mainMenuText[1]->setFont(font);
    mainMenuText[1]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[1]->setString("Make a Map");
    mainMenuText[1]->setPosition(sf::Vector2f(width / 2, height / 3));

    //Options
    mainMenuText[2]->setFont(font);
    mainMenuText[2]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[2]->setString("Options");
    mainMenuText[2]->setPosition(sf::Vector2f(width / 2, height / 2));

    //About
    mainMenuText[3]->setFont(font);
    mainMenuText[3]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[3]->setString("About");
    mainMenuText[3]->setPosition(sf::Vector2f(width / 2, height * 4 / 6));

    //Quit
    mainMenuText[4]->setFont(font);
    mainMenuText[4]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[4]->setString("Quit");
    mainMenuText[4]->setPosition(sf::Vector2f(width / 2, height * 5 / 6));
}

//the initial loading menu

void MainMenu::draw()
{
    int mouseX;
    int mouseY;

    

        //clear and redraw the frame with updated text
        window->clear(ColorSchemeConstants::BACKGROUND_COLOR);
        for(sf::Text* text : mainMenuText){
            window->draw(*text);
        }
        window->display();
    
}

//decrements the menuSelected index integer to go up in the menu
void MainMenu::moveUp(){
    //set currently selected to white
    mainMenuText[menuSelected]->setFillColor(ColorSchemeConstants::TEXT_COLOR);

    //decrement menuSelected
    menuSelected--;

    //check if <0
    //<0 -> set to 4 = go to bottom
    if(menuSelected < 0){
        menuSelected = 4; //4 is the bottom of the menu
    }
    //set menuSelected color to accent color
    mainMenuText[menuSelected]->setFillColor(ColorSchemeConstants::ACCENT_COLOR);

}

//increments the menuSelected index integer to go down in the menu
void MainMenu::moveDown(){
    //set currently selected to white
    mainMenuText[menuSelected]->setFillColor(ColorSchemeConstants::TEXT_COLOR);

    //increment menuSelected
    menuSelected++;

    //check if >4
    //>4 -> set to 0 = got to top
    if(menuSelected > 4){
        menuSelected = 0; //4 is the top of the menu
    }
    //set menuSelected color to accent color
    mainMenuText[menuSelected]->setFillColor(ColorSchemeConstants::ACCENT_COLOR);
}
