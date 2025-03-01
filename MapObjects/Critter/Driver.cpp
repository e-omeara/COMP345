#include <iostream>
#include <vector>
#include "Map.h"
#include "MapObserver.h"
#include "MapGraphics.h"
#include "SFMLCritterSimulator.h"
#include "Critter.h"

//Coord to Position Index Converting function
Position coordToPosition(const coord &c) {
    Position p;
    p.x = c.x;
    p.y = c.y;
    return p;
}

int main(){
    //Map-Making Test Case
    MapObserver* observer = new MapObserver;
    Map* map = new Map(20, 10);
    map->getObserver(observer);
    MapGraphics graphics(observer, map);
    graphics.runGame();  // user creates the map/path here.
    
    //Getting the made path from the map.
    std::vector<coord> cpath = map->getPath();
    if(cpath.empty()){
        std::cerr << "Error: Path is empty." << std::endl;
        return 1;
    }
    std::vector<Position> path;
    for(auto &c : cpath)
        path.push_back(coordToPosition(c));
    
    //Critter Test Case
    SFMLCritterSimulator simulator(map, path);
    simulator.runSimulation();

    delete map;
    delete observer;
    return 0;
}