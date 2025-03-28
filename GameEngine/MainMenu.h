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
        sf::Text* mainMenuText[4]; // 0 = load map , 1 = make map , 2 = options , 3 = about , 4 = quit
        sf::RenderWindow* window;

    //functions
    public:

        MainMenu(float width, float height, sf::RenderWindow* window, sf::Font font);
        void draw();
        void moveUp();
        void moveDown();

    private:



};

#endif