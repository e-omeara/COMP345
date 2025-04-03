#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "MapObserver.h"
#include <vector>

using namespace std;
/*
struct coord{
            int x;
            int y;
};*/

class Map{


    private:

        
        bool isMaking;
        int height;
        int width;
        vector<char> map;
        vector<coord> path;
        int makeX;
        int makeY;
        char prevDir;
        MapObserver* observer;

    public:

        Map(int x, int y);

        Map();

        void getObserver(MapObserver* plugin);

        void printMap();

        string stringMap();

        //friend class MapMaker;

        //getter methods
        vector<coord> getPath();

        vector<char> getMap();

        int getWidth();

        int getHeight();

        int upgrade(char type, int xPos, int yPos);

        //methods to make the map
        void initiateMaking();

        void resize(int x, int y);

        void setEntrance(int x, int y);

        void laypath(char dir);

        int setExit();

        int setTower(int x, int y);

        void printMapMaker();

        void saveMap();

        int loadMap(string fileName);

        vector<string> getMapList();

    private:

        void updateObserver(string msg);

        int getPos(int x, int y);



};



#endif













