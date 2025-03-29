#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Menu.h"

//constructor
OptionsMenu::OptionsMenu(sf::RenderWindow* theWindow, sf::Font& font) 
     : font(font) , window(theWindow) {

     selection = 0; //top
     createMenuText();
}

void OptionsMenu::createMenuText(){
    int width = window->getSize().x;
    int height = window->getSize().y;

    for(int i = 0; i < 5; i++){
        menuText[i] = new sf::Text(font);
        menuText[i]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
        menuText[i]->setCharacterSize(15);
    }

    menuText[0]->setFillColor(ColorSchemeConstants::ACCENT_COLOR); //whatever is currently selected is ACCENT_COLOR
    menuText[0]->setString("blah blah blah options stuff");
    menuText[0]->setPosition(sf::Vector2f(25, height * 1 / 6));

    menuText[1]->setString("baltimore accent challenge");
    menuText[1]->setPosition(sf::Vector2f(25, (height * 1 / 6)+30));

    menuText[2]->setString("beanie");
    menuText[2]->setPosition(sf::Vector2f(25, (height * 1 / 6)+60));

    menuText[3]->setString("jitt");
    menuText[3]->setPosition(sf::Vector2f(25, (height * 1 / 6)+90));

    menuText[4]->setString("Back");
    menuText[4]->setPosition(sf::Vector2f(25, (height * 1 / 6)+120));
}

//draws main menu | DOES NOT LOOP... MUST LOOP FUNCTION !!
void OptionsMenu::draw(){
    //clear and redraw the frame with updated text
    window->clear(ColorSchemeConstants::BACKGROUND_COLOR);

    //drawing menu depending
     menuText[selection]->setFillColor(ColorSchemeConstants::ACCENT_COLOR); //whatever is currently selected is ACCENT_COLOR
     for(int i = 0; i < 5; i++){
          window->draw(*menuText[i]);
     }
    window->display();


}

//decrements the selection index integer to go up in the menu
void OptionsMenu::moveUp(){
    //set currently selected to white
    menuText[selection]->setFillColor(ColorSchemeConstants::TEXT_COLOR);

    //decrement selection
    selection--;

    //check if <0
    //<0 -> set to 4 = go to bottom
    if(selection < 0){
        selection = 4; //4 is the bottom of the menu
    }

    //set selection color to accent color
    menuText[selection]->setFillColor(ColorSchemeConstants::ACCENT_COLOR);


    this->draw();
}

//increments the selection index integer to go down in the menu
void OptionsMenu::moveDown() {
    //set currently selected to white
    menuText[selection]->setFillColor(ColorSchemeConstants::TEXT_COLOR);

    //increment selection
    selection++;

    //check if >4
    //>4 -> set to 0 = got to top
    if(selection > 4){
        selection = 0; //4 is the top of the menu
    }
    //set selection color to accent color
    menuText[selection]->setFillColor(ColorSchemeConstants::ACCENT_COLOR);
}

void OptionsMenu::select(){
     return;
}
