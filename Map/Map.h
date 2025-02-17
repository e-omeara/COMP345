#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

struct coord{
            int x;
            int y;
};

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

    public:

        Map(int x, int y);

        void printMap();

        friend class MapMaker;

        //getter methods
        vector<coord> getPath();

        vector<char> getMap();

        int getWidth();

        int getHeight();



        //methods to make the map
        void initiateMaking();

        void setEntrance(int x, int y);

        void laypath(char dir);

        void setExit();

        void printMapMaker();

    private:


        int getPos(int x, int y);



};



#endif













