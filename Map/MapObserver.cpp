#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "MapObserver.h"



MapObserver::MapObserver(){

    height = 0;
    width = 0;
    map.resize(1, '-');
    coord orig;
    orig.x = 0;
    orig.y = 0;
    path.resize(1, orig);
    makeX = 0;
    makeY = 0;
    status = "null";
    message = "no message";


}

void MapObserver::update(int nheight, int nwidth, vector<char> nmap, vector<coord> npath, int nmakeX, int nmakeY, string nstatus, string nmsg){
    height = nheight;
    width = nwidth;
    map = nmap;
    path = npath;
    makeX = nmakeX;
    makeY = nmakeY;
    status = nstatus;
    message = nmsg;

}

void MapObserver::update(string msg){
    message = msg;
}

string MapObserver::getMessage(){
    return message;

}

vector<char> MapObserver::getMap(){
    return map;
}


int MapObserver::getHeight(){
    return height;
}


int MapObserver::getWidth(){
    return width;
}

void MapObserver::ping(){
    cout << "ping";
}








