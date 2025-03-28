#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "MainMenu.h"

//constructor
MainMenu::MainMenu(sf::RenderWindow* theWindow, sf::Font& font) 
    : font(font) , window(theWindow) {
    if(!font.openFromFile("Arial Unicode.ttf")){
        cerr << "unable to load font from file";
        return;
    }

    menuSelected = 0;

    int width = window->getSize().x;
    int height = window->getSize().y;
    // Load Map
    //default selection
    mainMenuText[0] = new sf::Text(font);    
    mainMenuText[0]->setFont(font);
    mainMenuText[0]->setFillColor(ColorSchemeConstants::ACCENT_COLOR); //whatever is currently selected is ACCENT_COLOR
    mainMenuText[0]->setString("Play");
    mainMenuText[0]->setCharacterSize(35);
    mainMenuText[0]->setPosition(sf::Vector2f(30, height / 6));

    // Make Map
    mainMenuText[1] = new sf::Text(font);
    mainMenuText[1]->setFont(font);
    mainMenuText[1]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[1]->setString("Make a Map");
    mainMenuText[1]->setCharacterSize(35);
    mainMenuText[1]->setPosition(sf::Vector2f(30, height / 3));

    //Options
    mainMenuText[2] = new sf::Text(font);
    mainMenuText[2]->setFont(font);
    mainMenuText[2]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[2]->setString("Options");
    mainMenuText[2]->setCharacterSize(35);
    mainMenuText[2]->setPosition(sf::Vector2f(30, height / 2));

    //About
    mainMenuText[3] = new sf::Text(font);
    mainMenuText[3]->setFont(font);
    mainMenuText[3]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[3]->setString("About");
    mainMenuText[3]->setCharacterSize(35);
    mainMenuText[3]->setPosition(sf::Vector2f(30, height * 4 / 6));

    //Quit
    mainMenuText[4] = new sf::Text(font);
    mainMenuText[4]->setFont(font);
    mainMenuText[4]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    mainMenuText[4]->setString("Quit");
    mainMenuText[4]->setCharacterSize(35);
    mainMenuText[4]->setPosition(sf::Vector2f(30, height * 5 / 6));
    
}

//draws main menu | DOES NOT LOOP... MUST LOOP FUNCTION !!
void MainMenu::draw(){
    //clear and redraw the frame with updated text
    window->clear(ColorSchemeConstants::BACKGROUND_COLOR);

    for(int i = 0; i < 5; i++){
        window->draw(*mainMenuText[i]);
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


    this->draw();
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
