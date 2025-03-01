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
        sf::RenderWindow window;
        vector<sf::RectangleShape> mapTiles;
        float tilelength;

        sf::RectangleShape scenery;
        sf::RectangleShape pathTile;
        sf::RectangleShape tower;
        sf::RectangleShape entry;
        sf::RectangleShape exit;


    //functions
    public:

        MapGraphics(MapObserver* plugin, Map* theMap);

        int runGame();

        int updatevisuals();

        string displayText(string title);

        int renderMap();

    private:

        int loadingmenu();
        int mapMaking();
        int placeTowers();
        coord getMapPos(int x, int y);


};

#endif