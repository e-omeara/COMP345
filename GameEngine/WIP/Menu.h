#ifndef MENU_H
#define MENU_H

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ColorSchemeConstants.h"

using namespace std;


class Menu {

    //attributes
     private:
          sf::Font font;
          int selection;
          std::vector<sf::Text*> menuText; // 0 = load map , 1 = make map , 2 = options , 3 = about , 4 = quit
          sf::RenderWindow* window;

     //functions
     public:

          //Menu(sf::RenderWindow* theWindow, sf::Font& font);
          virtual void draw() = 0;
          virtual void moveUp() = 0;
          virtual void moveDown() = 0;
          virtual void select() = 0;

     private:
          virtual void createMenuText() = 0;


};

class MainMenu : Menu{
    //attributes
    private:

        sf::Font font;
        int selection;
        int currentMenuID; //corresponds to mainMenuText indeces, main menu is -1
        std::vector<sf::Text*> menuText; // 0 = load map , 1 = make map , 2 = options , 3 = about , 4 = quit
        sf::RenderWindow* window;

    //functions
    public:

          MainMenu(sf::RenderWindow* theWindow, sf::Font& font);
          void draw() override;
          void moveUp() override;
          void moveDown() override;
          void select() override;

     private:
          void createMenuText() override;
};

class OptionsMenu : Menu{
     //attributes
     private:
 
          sf::Font font;
          int selection;
          std::vector<sf::Text*> menuText;
          sf::RenderWindow* window;
          int currentMenuID;
     //functions
     public:
 
           OptionsMenu(sf::RenderWindow* theWindow, sf::Font& font);
           void draw() override;
           void moveUp() override;
           void moveDown() override;
           void select() override;
 
     private:
          void createMenuText() override;
 };

 class AboutMenu : Menu{
     //attributes
     private:
 
         sf::Font font;
         int selection;
         std::vector<sf::Text*> menuText; // 0 = load map , 1 = make map , 2 = options , 3 = about , 4 = quit
         sf::RenderWindow* window;
 
     //functions
     public:
 
           AboutMenu(sf::RenderWindow* theWindow, sf::Font& font);
           void draw() override;
           void moveUp() override;
           void moveDown() override;

     private:
          void createMenuText() override;
 };
#endif