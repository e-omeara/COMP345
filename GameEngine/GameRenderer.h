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



class GameRenderer {

    private:
     sf::RenderWindow* window;
     MapGraphics* mapGraphics;
     Map* map;
     Player* player;
     bool isPlaying;
     SFMLCritterSimulator* critSim;
     Towers* myTower;
    


    public:
     GameRenderer(Player* player, Map* map, MapGraphics* mapGraphics, SFMLCritterSimulator* crSim);
     void startGame();
     void mainWindow();
     void makeMapWindow();
     void playTime();
     void pauseTime();
     void endGame();


    private:
     void inputLogic();


};