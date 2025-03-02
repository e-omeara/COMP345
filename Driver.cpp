#include <vector>
#include <iostream>
#include "Towers.h"
#include "TowerObserver.h"
#include "Critter.h"
#include "Map.h"
#include "MapObserver.h"
#include "MapGraphics.h"
#include "SFMLCritterSimulator.h"

Position coordToPosition(const coord &c) {
   Position p;
   p.x = c.x;
   p.y = c.y;
   return p;
}


int main() {

   //Map-Making Test Case
   MapObserver* mapobserver = new MapObserver;
   Map* map = new Map(20, 10);
   map->getObserver(mapobserver);
   MapGraphics graphics(mapobserver, map);
   graphics.runGame();  // user creates the map/path here.
   
   //Getting the made path from the map.
   std::vector<coord> cpath = map->getPath();
   if(cpath.empty()){
      std::cerr << "Error: Path is empty." << std::endl;
      return 1;
   }
   std::vector<Position> path1;
   for(auto &c : cpath)
      path1.push_back(coordToPosition(c));
   
   //Critter Test Case
   SFMLCritterSimulator simulator(map, path1);
   simulator.runSimulation();

   delete map;
   delete mapobserver;
   //return 0;



   //Tower examples
    std::cout << "Creating example towers and critters!" << std::endl;

    double balance = 1000;

    Towers archer("archer", {0,0});
    Towers ballista("ballista", {0,0});
    Towers catapult("catapult", {50,50});

    TowerObserver observer(archer);

    /* std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Archer Cost: " << archer.getBuyingCost() << std::endl;
    std::cout << "Archer Refund: " << archer.getRefundValue() << std::endl;
 */
    std::vector<Position> path { {0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0} };
    Critter enemy(20, 1, 3, 1, 7, path);
    

    /* std::cout << "Critter health is at " << enemy.getHP() << std::endl;
    archer.shoot(enemy);

    ballista.shoot(enemy); 
 
    catapult.shoot(enemy);  

    std::cout << "Critter health is at " << enemy.getHP() << std::endl; */

    archer.levelUp(balance);
    archer.levelUp(balance);

    /* std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Balance: " << balance << std::endl;
 */
    return 0;

    
}