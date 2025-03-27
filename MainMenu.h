#ifndef MENUGRAPHICS_H
#define MENUGRAPHICS_H



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

        sf::Text menuText;
        static const sf::Color primaryColor();
        static const sf::Color secondaryColor();
        static const sf::Color accentColor();
        static const sf::Color backgroundColor();

        




        sf::RectangleShape background;

    //functions
    public:

        MainMenu();

        int runGame();

        int updatevisuals();

        string displayText(string title);

    private:

        int loadingmenu();


};

#endif