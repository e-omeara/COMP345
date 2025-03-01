#include <vector>
#include <iostream>
#include "Towers.cpp"
#include "Critter.cpp"

int main() {
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