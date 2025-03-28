#ifndef MAINMENU_H
#define MAINMENU_H



#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapObserver.h"
#include "Map.h"

using namespace std;


int mainfunc();


class MainMenu {

    //attributes
    private:

        sf::RenderWindow window;


        sf::RectangleShape background;

    //functions
    public:

        //MainMenu(sf::Text menuText, sf::Window renderWindow);

        MainMenu();

        int showMenu();

        int updatevisuals();

        string displayText(string title);

    private:



};

#endif