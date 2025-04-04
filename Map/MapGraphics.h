#ifndef MAPGRAPHICS_H
#define MAPGRAPHICS_H



#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapObserver.h"
#include "Map.h"

using namespace std;


int mainfunc();


class MapGraphics {

    //attributes
    private:

        MapObserver* observer;
        Map* map;
        //sf::RenderWindow window;
        vector<sf::RectangleShape> mapTiles;
        float tilelength;
        float topCorner;

        sf::RectangleShape scenery;
        sf::RectangleShape pathTile;
        sf::RectangleShape tower;
        sf::RectangleShape entry;
        sf::RectangleShape exit;
        sf::RectangleShape upgrade;
        sf::RectangleShape fire;
        sf::RectangleShape ice;


    //functions
    public:

        MapGraphics(MapObserver* plugin, Map* theMap);

        int runGame();

        int updatevisuals();

        string getSaveName(sf::RenderWindow* window);

        string displayText(string title);

        int renderMap(sf::RenderWindow* window);

        int getParameters(sf::RenderWindow* window);
        int mapMaking(sf::RenderWindow* theWindow);

        int loadingMap(sf::RenderWindow* window, vector<string> mapVect);

        int viewMap(sf::RenderWindow* window);

    private:

        //int loadingmenu();
        
        //int placeTowers();
        coord getMapPos(int x, int y);


};

#endif