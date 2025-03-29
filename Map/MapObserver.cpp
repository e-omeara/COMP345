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

void MapObserver::update(int nheight, int nwidth, const vector<char>& nmap, const vector<coord>& npath, int nmakeX, int nmakeY, const string& nstatus, const string& nmsg){
    cerr << "\nentered MapObserver::update()";
    height = nheight;
    cerr << "height";
    width = nwidth;
    cerr << "width";
    map = nmap;
    cerr << "map";
    path = npath;
    cerr << "path";
    makeX = nmakeX;
    cerr << "makeX";
    makeY = nmakeY;
    cerr << "makeY";
    status = nstatus;
    cerr << "status";
    message = nmsg;
    cerr << "\nFinished MapObserver::update()";

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








