#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Player {

    public:
        static int balance;
        
    
        static void renderBalance(sf::RenderWindow *window);
        static void initializePlayer(int amount);
        static void addToAmount(int add);



};