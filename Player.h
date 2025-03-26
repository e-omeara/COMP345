#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Player {

    public:
        int balance;
        int health;
        Player(int amount, int hp);
        
        //Render the coin balance and player's health on the provided window.
        void renderBalance(sf::RenderWindow *window);
        void initializePlayer(int amount);
        void addToAmount(int add);
        void reduceHealth(int dmg);

        //Getters
        int getBalance() const { return balance; }
        int getHealth() const { return health; }

    private:
    
        sf::Font font;
        void loadResource();

};

#endif