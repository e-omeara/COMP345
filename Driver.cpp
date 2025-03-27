#include <vector>
#include <iostream>
#include "Towers.h"
#include "TowerObserver.h"
#include "Critter.h"
#include "Map.h"
#include "MapObserver.h"
#include "MapGraphics.h"
#include "TowerSimulator.h"
#include "SFMLCritterSimulator.h"
#include "GameRenderer.h"
#include "Player.h"
#include "TowerDecorator.h"
#include "ValueModifierDecorator.h"

Position coordToPosition(const coord &c) {
   Position p;
   p.x = c.x;
   p.y = c.y;
   return p;
}


int main() {
   std::cout << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << std::endl;







 //testing game engine and renderer
 MapObserver* mapobserver = new MapObserver;
 Map* map = new Map(20, 10);
 map->getObserver(mapobserver);

 MapGraphics *mgraphics = new MapGraphics(mapobserver, map);

 Player* player = new Player(100, 100);

 std::vector<Position> critterPath;
 for(auto &c : map->getPath())
   { critterPath.push_back(coordToPosition(c));}
 
 SFMLCritterSimulator* critSim;

 GameRenderer renderer(player, map, mgraphics, critSim);

 renderer.startGame();

 delete critSim;
 delete mapobserver;
 delete map;
 delete mgraphics;
 delete player;
 



//Tower Decorator Test Cases

std::cout << "Hello, World!" << std::endl;

double balance = 1000;

Towers* archer = new Towers("archer", {5,5});
Towers ballista("ballista", {0,0});
Towers catapult("catapult", {50,50});

TowerObserver* observer = new TowerObserver(*archer);

TowerSimulator tSim(observer , archer);
tSim.runGame();







//testing targeting strategy

std::vector<Position> mypath { {4,3}, {4,4}, {4,5}, {4,6}, {5,6}, {6,6}, {6,7}, {7,7}, {8,6}, {9,5}, {10,6}, {10,7}, {9,7}, {8,7}, {8,8}, {9,9} };
Towers mytower("archer", {5, 5}, 'n');
CritterGroup newcrits(1, mypath);
vector<Critter> mycritvector = newcrits.getCritters();
vector<Critter*> mycritters;
int moves = 0;
for(auto &c : mycritvector){
   for(int i = 0; i < moves/2; i++){
      c.move();
   }
   moves++;
   mycritters.push_back(&c);
}
//mytower.findTarget(mycritters);
Critter* critt = mytower.findTarget(mycritters);
mytower.shoot(*critt);


for(int j = 0; j < 9; j++){
   for(auto &c : mycritters){
      c->move();
   }
   critt = mytower.findTarget(mycritters);
   mytower.shoot(*critt);
   

}
















//Tower
/*
std::vector<Position> path { {0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0} };
Critter enemy(20, 1, 3, 1, 7, path);


std::cout << "Initial Stats: " << std::endl;
std::cout << "Level: " << ballista.getLevel() << std::endl;
std::cout << "Cost: " << ballista.getBuyingCost() << std::endl;
std::cout << "Refund: " << ballista.getRefundValue() << std::endl;
std::cout << "Range: " << ballista.getRange() << std::endl;
std::cout << "Power: " << ballista.getPower() << std::endl;
std::cout << "Rate Of Fire: " << ballista.getRateOfFire() << std::endl;
ValueModifierDecorator upgradedBallista("ballista", {3,3}, ballista, 20, 10, 1, 2, 100);
std::cout << "Upgraded Stats: " << std::endl;
std::cout << "Level: " << upgradedBallista.getLevel() << std::endl;
std::cout << "Cost: " << upgradedBallista.getBuyingCost() << std::endl;
std::cout << "Refund: " << upgradedBallista.getRefundValue() << std::endl;
std::cout << "Range: " << upgradedBallista.getRange() << std::endl;
std::cout << "Power: " << upgradedBallista.getPower() << std::endl;
std::cout << "Rate Of Fire: " << upgradedBallista.getRateOfFire() << std::endl;


*/





















/*
 //Getting the made path from the map.
 std::vector<coord> cpath = map->getPath();
 if(cpath.empty()){
    std::cerr << "Error: Path is empty." << std::endl;
    return 1;
 }
 std::vector<Position> critterPath;
 for(auto &c : cpath)
    critterPath.push_back(coordToPosition(c));
 
 //Critter Test Case
 SFMLCritterSimulator simulator(map, critterPath);
 simulator.runSimulation();





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

    Towers* archer = new Towers("archer", {2,2});
    Towers ballista("ballista", {0,0});
    Towers catapult("catapult", {50,50});

    TowerObserver* observer = new TowerObserver( *archer);

    TowerSimulator tSim(observer , archer);
    tSim.runGame();

     std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Archer Cost: " << archer.getBuyingCost() << std::endl;
    std::cout << "Archer Refund: " << archer.getRefundValue() << std::endl;
 
    std::vector<Position> path { {0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0} };
    Critter enemy(20, 1, 3, 1, 7, path);
    

     std::cout << "Critter health is at " << enemy.getHP() << std::endl;
    archer.shoot(enemy);

    ballista.shoot(enemy); 
 
    catapult.shoot(enemy);  

    std::cout << "Critter health is at " << enemy.getHP() << std::endl; 

    archer->levelUp(balance);
    archer->levelUp(balance);

     std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Balance: " << balance << std::endl;
 */

 
    return 0;

    
}