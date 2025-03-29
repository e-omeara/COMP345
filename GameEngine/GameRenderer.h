#ifndef GAMERENDERER_H
#define GAMERENDERER_H

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
#include "CritterFactory.h"
#include "ColorSchemeConstants.h"



class GameRenderer {

    private:
    //window to be used by simulator classes
     sf::RenderWindow* window;
     //map graphics class
     MapGraphics* mapGraphics;
     //map class has map and path
     Map* map;
     //player class has balance and health
     Player* player;
     //game status
     bool isPlaying;
     //critter simulator
     SFMLCritterSimulator* critSim;
     //tower class -> TODO: turn into tower vector...?
     Towers* myTower;
     //
     TowerSimulator* tSim;
    


    public:
    //constructor
     GameRenderer(Player* player, Map* map, MapGraphics* mapGraphics, SFMLCritterSimulator* crSim, TowerSimulator* t0Sim);
     // entry point to game
     void startGame();
     //main menu
     int mainWindow();
     //make map
     void makeMapWindow();
     //critter attack phase
     void playTime();
     //tower purchase phase
     void pauseTime();
     //Initial tower purchase phase
     void pauseTimeInit();
     //end graphics and stats
     void endGame();


    private:
    //TODO: delete???
     void inputLogic();


};

#endif