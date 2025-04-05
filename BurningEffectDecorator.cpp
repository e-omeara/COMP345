#include "BurningEffectDecorator.h"



BurningEffectDecorator::BurningEffectDecorator(std::string type, Position pos, Towers tower, double burnDamage, int duration)
 : TowerDecorator(type, pos, tower), burnDamagePerTick(burnDamage), burnDuration(duration) {

}

void BurningEffectDecorator::shoot(Critter &critter) {

    // Apply normal damage
    Towers::shoot(critter);
    std::cout << "Fire shoot!" << std::endl;
        
    // Apply burning effect
    burningEnemies[&critter] = burnDuration;
    std::cout << "Enemy set on fire for " << burnDuration << " ticks!" << std::endl;

}


void BurningEffectDecorator::updateBurningEffects(){
    auto it = burningEnemies.begin();
    while (it != burningEnemies.end()) 
    {
        Critter* critter = it->first;
        int& remainingDuration = it->second;
        if(critter->isAlive())
        {
            // Apply burn damage
            critter->takeDamage(burnDamagePerTick);
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
        else
        {
            it = burningEnemies.erase(it);
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