#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

struct coord{
    int x;
    int y;
};


class MapObserver{

    private:
        int height;
        int width;
        vector<char> map;
        vector<coord> path;
        int makeX;
        int makeY;
        string status;
        string message;

    public:

        MapObserver();
    
        void update(int nheight, int nwidth, vector<char> nmap, vector<coord> npath, int nmakeX, int nmakeY, string nstatus, string nmsg);

        void update(string msg);

        void ping();

        string getMessage();

};


#endif