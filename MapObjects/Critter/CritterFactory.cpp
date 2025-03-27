#include "CritterFactory.h"
#include "Critter.h"
#include <iostream>

std::vector<Critter*> CritterFactory::createWave(int waveLevel, const std::vector<Position>& path) {
    std::vector<Critter*> critters;
    
    //Wave 1 gets 3 Fast and 3 Tank critters, every other wave adds one more of each. One boss per wave
    int countFast = 3 + (waveLevel - 1);
    int countTank = 3 + (waveLevel - 1);
    int countBoss = 1; // Always one Boss per wave

    //Scaling increments for increased difficulty
    int fastHpIncrement = 5;
    int fastStrengthIncrement = 2;
    
    int tankHpIncrement = 10;
    int tankStrengthIncrement = 3;
    
    int bossHpIncrement = 20;
    int bossStrengthIncrement = 5;

    //Create FastCritters
    for (int i = 0; i < countFast; i++) {
        FastCritter* fc = new FastCritter(path);
        if (waveLevel > 1) {
            fc->setHP(fc->getHP() + (waveLevel - 1) * fastHpIncrement);
            fc->setStrength(fc->getStrength() + (waveLevel - 1) * fastStrengthIncrement);
        }
        critters.push_back(fc);
    }
    //Create TankCritters
    for (int i = 0; i < countTank; i++) {
        TankCritter* tc = new TankCritter(path);
        if (waveLevel > 1) {
            tc->setHP(tc->getHP() + (waveLevel - 1) * tankHpIncrement);
            tc->setStrength(tc->getStrength() + (waveLevel - 1) * tankStrengthIncrement);
        }
        critters.push_back(tc);
    }
    //Create BossCritter
    for (int i = 0; i < countBoss; i++) {
        BossCritter* bc = new BossCritter(path);
        if (waveLevel > 1) {
            bc->setHP(bc->getHP() + (waveLevel - 1) * bossHpIncrement);
            bc->setStrength(bc->getStrength() + (waveLevel - 1) * bossStrengthIncrement);
        }
        critters.push_back(bc);
    }
    
    return critters;
}
