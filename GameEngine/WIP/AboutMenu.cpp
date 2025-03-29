#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Menu.h"

//constructor
AboutMenu::AboutMenu(sf::RenderWindow* theWindow, sf::Font& font) 
    : font(font) , window(theWindow) {

    selection = 0; //top

    createMenuText();
}

void AboutMenu::createMenuText(){
    int width = window->getSize().x;
    int height = window->getSize().y;

    menuText[0] = new sf::Text(font);
    menuText[0]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    menuText[0]->setCharacterSize(15);
    menuText[0]->setString("fortnite battlepass");
    menuText[0]->setPosition(sf::Vector2f(45, height / 2));

}

//draws main menu | DOES NOT LOOP... MUST LOOP FUNCTION !!
void AboutMenu::draw(){
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
void AboutMenu::moveUp(){
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
void AboutMenu::moveDown() {
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
