#ifndef TOWER_SIM_H
#define TOWER_SIM_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "TowerObserver.h"
#include "Towers.h"
#include "Map.h"
#include "Player.h"
#include "SFMLCritterSimulator.h"
#include "Critter.h"
#include "ColorSchemeConstants.h"
#include "ValueModifierDecorator.h"
#include "SlowingEffectDecorator.h"
#include "BurningEffectDecorator.h"

using namespace std;

class TowerSimulator{


    private:
    //attributes
    //TowerObserver* tObserver;
    vector<Towers*>* towers;
    vector<BurningEffectDecorator*>* burners;
    vector<SlowingEffectDecorator*>* icers;
    bool placing;
    Map* map;
    Player* player;
    char selected;
    int towerSelect;
    



    public:
    //methods
    //Constructors
    TowerSimulator(vector<Towers*>* mytowers);
    TowerSimulator(Player* thePlayer);
    TowerSimulator();
    ~TowerSimulator();
    //add map
    int addMap(Map* theMap);
    //entry point to simulator
    int runGame();
    //create the window
    int createWindow();
    //render the hover stats
    int renderTowers(sf::RenderWindow* window);
    //TODO: create tower menu items
    int renderPurchaseMenu(sf::RenderWindow* window);
    //Create reaction to "click"
    int click(sf::RenderWindow* window);
    //
    void shoot(SFMLCritterSimulator* critSim);
    

    




    private:
    //methods
};



#endif