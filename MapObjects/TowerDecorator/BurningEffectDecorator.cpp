#include "BurningEffectDecorator.h"
#include <string>



BurningEffectDecorator::BurningEffectDecorator(std::string type, Position pos, Towers tower, double burnDamage, int duration)
 : TowerDecorator(type, pos, tower), burnDamagePerTick(burnDamage), burnDuration(duration) {

}

void BurningEffectDecorator::shoot(Critter &critter) {

    // Apply normal damage
    decoratedTower.shoot(critter);
    std::cout << "Fire shoot!" << std::endl;
        
    // Apply burning effect
    burningEnemies[&critter] = burnDuration;
    std::cout << "Enemy set on fire for " << burnDuration << " ticks!" << std::endl;

}


void BurningEffectDecorator::updateBurningEffects(){
    auto it = burningEnemies.begin();
    while (it != burningEnemies.end()) {
        Critter* critter = it->first;
        int& remainingDuration = it->second;
        
        // Apply burn damage
        critter->setHP(critter->getHP() - burnDamagePerTick);
        std::cout << "Burning damage of " << burnDamagePerTick << " applied! Remaining HP: " << critter->getHP() << std::endl;
        
        // Decrease duration
        remainingDuration--;
        
        // Remove if duration expired
        if (remainingDuration <= 0) {
            it = burningEnemies.erase(it);
        } else {
            ++it;
        }
    }
}
//getter methods
double BurningEffectDecorator::getBurnDamage(){
    return burnDamagePerTick;
}

double BurningEffectDecorator::getBurnDuration(){
    return burnDuration;
}