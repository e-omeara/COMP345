#ifndef MAPMAKER_H
#define MAPMAKER_H


#include <iostream>
#include "Map.h"

using namespace std;

//runs the program
void startMapMaker();

//asks user for map dimensions & makes new map
Map createMap();


//asks user for entrance coords and then calls Map::setEntrance
void setEntrance(int x, int y);

void editMap(Map map);
//takes user input, calls Map::layMap
//user input also asks if user wants to place exit at current location > calls Map::setExit
//calls Map::printMapMaker() after every edit


//clear and show "you're playing the game now"
void startGame();

//clear and show "youre in the main menu" place holder for mm
void backToMain();

#endif