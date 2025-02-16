#include <iostream>
#include "MapObjects/Towers.cpp"
#include "MapObjects/Critter.cpp"
#include "Map/MapMaker.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    double balance = 1000;

    Towers archer = Towers("archer", {0,0});
    Towers ballista = Towers("ballista", {0,0});
    Towers catapult = Towers("catapult", {50,50});

    /* std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Archer Cost: " << archer.getBuyingCost() << std::endl;
    std::cout << "Archer Refund: " << archer.getRefundValue() << std::endl;
 */
    std::vector<Position> path = { {0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0}, {7,0} };
    Critter enemy = Critter(20, 1, 3, 1, 7, path);
    

    std::cout << "Critter health is at " << enemy.getHP() << std::endl;
    /* archer.shoot(enemy);

    ballista.shoot(enemy); */
 
    catapult.shoot(enemy);  

    std::cout << "Critter health is at " << enemy.getHP() << std::endl;

    archer.levelUp(balance);

    std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Balance: " << balance << std::endl;

    return 0;
}