#include <iostream>
#include "MapObjects/Towers.h"
#include "MapObjects/Critter.h"
#include "Map/MapMaker.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    double balance = 1000;

    Position origin;
    origin.x = 0;
    origin.y = 0;

    std::vector<Position> path;
    Position patharray[8];
    for(int i = 0; i < 8; i++){
        patharray[i].x = i;
        patharray[i].y = 0;
        path.push_back(patharray[i]);

    }

    
    std::string archerString = "archer";
    std::string ballistaString = "ballista";
    std::string catapultString = "catapult";
    Towers archer(archerString, origin);
    Critter enemy = Critter(20, 1, 3, 1, 7, path);
    Towers ballista = Towers(ballistaString, origin);
    Towers catapult = Towers(catapultString, origin);

    std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Archer Cost: " << archer.getBuyingCost() << std::endl;
    std::cout << "Archer Refund: " << archer.getRefundValue() << std::endl;
 
    
    
 
    std::cout << "Critter health is at " << enemy.getHP() << std::endl;
     archer.shoot(enemy);

    ballista.shoot(enemy); 
 
    catapult.shoot(enemy);  

    

    std::cout << "Critter health is at " << enemy.getHP() << std::endl;

    archer.levelUp(balance);

    std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Balance: " << balance << std::endl;

    return 0;

    
}