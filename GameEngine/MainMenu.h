#ifndef MAINMENU_H
#define MAINMENU_H

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ColorSchemeConstants.h"

using namespace std;


class MainMenu {

    //attributes
    private:

        sf::Font font;
        int menuSelected;
        int currentMenuID; //corresponds to mainMenuText indeces, main menu is -1
        sf::Text* mainMenuText[5]; // 0 = load map , 1 = make map , 2 = options , 3 = about , 4 = quit
        sf::Text* optionsText[5];
        sf::Text* aboutText;
        sf::RenderWindow* window;

    //functions
    public:

        MainMenu(sf::RenderWindow* theWindow, sf::Font& font);
        int draw();
        void moveUp();
        void moveDown();
        void selectMenu();

    private:
    void createMenuText();


};

#endif