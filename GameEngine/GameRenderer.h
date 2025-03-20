#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include "Towers.h"
#include "TowerObserver.h"
#include "Critter.h"
#include "Map.h"
#include "MapObserver.h"
#include "MapGraphics.h"
#include "TowerSimulator.h"
#include "SFMLCritterSimulator.h"



class GameRenderer {

    public:
    static sf::RenderWindow* theWindow;


    
    static void initialize();
    static void mainWindow();
    static void makeMapWindow();
    static void playTime();
    static void pauseTime();
    static void endGame();


    private:
    static void inputLogic();


};