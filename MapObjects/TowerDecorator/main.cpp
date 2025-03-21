#include <iostream>
#include "Towers.h"
#include "critter.h"
#include "TowerDecorator.h"
#include "BurningEffectDecorator.h"
#include "SlowingEffectDecorator.h"
#include "ValueModifierDecorator.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

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

    /*archer.levelUp(balance);
    archer.levelUp(balance);*/

    /* std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Balance: " << balance << std::endl;
 */

   // Create a burning effect catapult
   /*BurningEffectDecorator burningCatapult("catapult", {1,1}, catapult, 3.0, 5);
   std::cout << "Initial enemy HP: " << enemy.getHP() << std::endl;
   burningCatapult.shoot(enemy);
   std::cout << "After Attack: " << enemy.getHP() << std::endl;
   for (int i = 0; i < burningCatapult.getBurnDuration(); i++) {
      std::cout << "Tick " << i+1 << " - ";
      burningCatapult.updateBurningEffects();
   }*/

   //create slowing effect archer
   /*SlowingEffectDecorator slowingArcher("archer", {2,2}, archer, 0.4, 5);
   std::cout << "Initial enemy Speed: " << enemy.getSpeed() << std::endl;
   slowingArcher.shoot(enemy);
   std::cout << "After attack: " << enemy.getSpeed() << std::endl;
   for (int i = 0; i < slowingArcher.getSlowDuration(); i++) {
      std::cout << "Tick " << i+1 << " - ";
      slowingArcher.updateSlowingEffects();
   }*/

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


    return 0;
}