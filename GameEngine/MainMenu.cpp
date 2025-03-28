#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "MainMenu.h"

//constructor
MainMenu::MainMenu(sf::RenderWindow* theWindow, sf::Font& font) 
    : font(font) , window(theWindow) {

    menuSelected = 0; //top
    currentMenuID = -1; //main menu

    createMenuText();
    
    
}

void MainMenu::createMenuText(){
    int width = window->getSize().x;
    int height = window->getSize().y;

    //CREATING MAIN MENU
    /*************************************************************************/

    for(int i = 0; i < 5; i++){
        mainMenuText[i] = new sf::Text(font);
        mainMenuText[i]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
        mainMenuText[i]->setCharacterSize(35);
    }

    //default selection
    mainMenuText[0]->setString("Play");
    mainMenuText[0]->setPosition(sf::Vector2f(30, height / 6));

    // Make Map
    mainMenuText[1]->setString("Make a Map");
    mainMenuText[1]->setPosition(sf::Vector2f(30, height / 3));

    //Options
    mainMenuText[2]->setString("Options");
    mainMenuText[2]->setPosition(sf::Vector2f(30, height / 2));

    //About
    mainMenuText[3]->setString("About");
    mainMenuText[3]->setPosition(sf::Vector2f(30, height * 4 / 6));

    //Quit
    mainMenuText[4]->setString("Quit");
    mainMenuText[4]->setPosition(sf::Vector2f(30, height * 5 / 6));
    /*************************************************************************/



    //CREATING OPTIONS MENU
    /*************************************************************************/

    for(int i = 0; i < 5; i++){
        optionsText[i] = new sf::Text(font);
        optionsText[i]->setFillColor(ColorSchemeConstants::TEXT_COLOR);
        optionsText[i]->setCharacterSize(15);
    }

    optionsText[0]->setFillColor(ColorSchemeConstants::ACCENT_COLOR); //whatever is currently selected is ACCENT_COLOR
    optionsText[0]->setString("blah blah blah options stuff");
    optionsText[0]->setPosition(sf::Vector2f(25, height * 1 / 6));

    optionsText[1]->setString("baltimore accent challenge");
    optionsText[1]->setPosition(sf::Vector2f(25, (height * 1 / 6)+30));

    optionsText[2]->setString("beanie");
    optionsText[2]->setPosition(sf::Vector2f(25, (height * 1 / 6)+60));

    optionsText[3]->setString("jitt");
    optionsText[3]->setPosition(sf::Vector2f(25, (height * 1 / 6)+90));

    optionsText[4]->setString("Back");
    optionsText[4]->setPosition(sf::Vector2f(25, (height * 1 / 6)+120));
    /*************************************************************************/



    //CREATING ABOUT MENU
    /*************************************************************************/
    aboutText = new sf::Text(font);
    aboutText->setFillColor(ColorSchemeConstants::TEXT_COLOR);
    aboutText->setCharacterSize(15);
    aboutText->setString("fortnite battlepass");
    aboutText->setPosition(sf::Vector2f(45, height / 2));
    /*************************************************************************/
}

//draws main menu | DOES NOT LOOP... MUST LOOP FUNCTION !!
void MainMenu::draw(){
    //clear and redraw the frame with updated text
    window->clear(ColorSchemeConstants::BACKGROUND_COLOR);

    //drawing menu depending on currentMenuID
    switch (currentMenuID){
        //cases 0 & 1 just run a function -> no menu to display. 4 quits
        case -1:{//main menu
            mainMenuText[menuSelected]->setFillColor(ColorSchemeConstants::ACCENT_COLOR); //whatever is currently selected is ACCENT_COLOR
            for(int i = 0; i < 5; i++){
                window->draw(*mainMenuText[i]);
            }
            break;
        }
        case 2 :{ // options
            optionsText[menuSelected]->setFillColor(ColorSchemeConstants::ACCENT_COLOR); //whatever is currently selected is ACCENT_COLOR
            for(int i = 0; i < 5; i++){
                window->draw(*optionsText[i]);
            }
            break;
        }
        case 3 :{ // about
            window->draw(*aboutText);
            break;
        }
        case 4 :{ // quit
            window->close();
            break;
        }
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

void MainMenu::selectMenu(){
    if(currentMenuID != -1){
        currentMenuID = -1;
        return;
    }
    currentMenuID = menuSelected;
}
