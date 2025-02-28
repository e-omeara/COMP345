#ifndef MAPGRAPHICS_H
#define MAPGRAPHICS_H



#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapObserver.h"
#include "Map.h"

using namespace std;



class MapGraphics {

    //attributes
    private:

        MapObserver* observer;
        Map* map;


    //functions
    public:

        MapGraphics(MapObserver* plugin, Map* theMap);

        int runGame();

        int updatevisuals();

        string displayText();

        int render();

    private:

        int loadingmenu();
        int MapMaking();


};

#endif