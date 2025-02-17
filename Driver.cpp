#include <vector>
#include <iostream>
#include "MapObjects/Towers.h"
#include "MapObjects/Critter.h"
#include "Map/MapMaker.h"


int main() {
    std::cout << "Creating example towers and critters!" << std::endl;

    double balance = 1000;

    Position origin;
    origin.x = 0;
    origin.y = 0;
    std::cout << "Creating generic path for critters...\n";
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
    Towers ballista = Towers(ballistaString, origin);
    Towers catapult = Towers(catapultString, origin);

    std::cout << "Example towers:\n";
//range power RoF
    std::cout << "Archer Tower: \nLevel: " << archer.getLevel()  <<
    " Cost: " << archer.getBuyingCost() <<
    " Refund Value: "<< archer.getRefundValue() << 
    " Range: " << archer.getRange() <<
    " Power:" << archer.getPower() <<
    " Rate of Fire: " << archer.getRateOfFire() << std::endl;
    
    std::cout << "Ballista Tower: \nLevel: " << ballista.getLevel()  <<
    " Cost: " << ballista.getBuyingCost() <<
    " Refund Value: "<< ballista.getRefundValue() << 
    " Range: " << ballista.getRange() <<
    " Power:" << ballista.getPower() <<
    " Rate of Fire: " << ballista.getRateOfFire() << std::endl;
    
    std::cout << "Catapult Tower: \nLevel: " << catapult.getLevel()  <<
    " Cost: " << catapult.getBuyingCost() <<
    " Refund Value: "<< catapult.getRefundValue() << 
    " Range: " << catapult.getRange() <<
    " Power:" << catapult.getPower() <<
    " Rate of Fire: " << catapult.getRateOfFire() << std::endl;
 
    std::cout << "Creating generic critter...\n";
    Critter enemy = Critter(20, 1, 3, 1, 7, path);

    std::cout << "Critter health is at " << enemy.getHP() << std::endl;
    std::cout << "Shooting the critter with the archer, the ballista, and the catapult.\n";
    archer.shoot(enemy);

    ballista.shoot(enemy); 
 
    catapult.shoot(enemy);  


    std::cout << "Critter health is at " << enemy.getHP() << std::endl;

    std::cout <<"Leveling up Archer Tower:\n";
    archer.levelUp(balance);

    std::cout << "Archer Level: " << archer.getLevel() << std::endl;
    std::cout << "Balance: " << balance << std::endl;
    
    std::cout << "\n\n\n";
    std::cout << "Creating example critter wave:\n";

    //Create Different Critter Types
    FastCritter fc(path);
    TankCritter tc(path);
    BossCritter bc(path);

    //Store them in a vector for testing
    std::vector<Critter*> critters = { &fc, &tc, &bc };

    //Testing five turns
    for (int turn = 0; turn < 5; ++turn) {
        std::cout << "\nTurn " << turn + 1 << ":\n";

        for (auto critter : critters) {
            critter->move();
            Position pos = critter->getPosition();
            std::cout << critter->getType() << " at (" << pos.x << ", " << pos.y << ") | HP: "
                      << critter->getHP() << " | Speed: " << critter->getSpeed() << " | Strength: "
                      << critter->getStrength() << "\n";
        }
    }

    std::cout << "Running MapMaker!\n";
    startMapMaker();
    
    return 0;

    
}