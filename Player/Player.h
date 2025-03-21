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
        
    
        void renderBalance(sf::RenderWindow *window);
        void initializePlayer(int amount);
        void addToAmount(int add);



};

#endif