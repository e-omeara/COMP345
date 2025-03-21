// BurningEffectDecorator.h
#ifndef BURNING_EFFECT_DECORATOR_H
#define BURNING_EFFECT_DECORATOR_H

#include "TowerDecorator.h"
#include <unordered_map>

// BurningEffectDecorator adds damage over time
class BurningEffectDecorator : public TowerDecorator {
private:
    double burnDamagePerTick;
    int burnDuration; // in game ticks
    
    // Track which critters are burning and for how long
    std::unordered_map<Critter*, int> burningEnemies;

public:
    BurningEffectDecorator(std::string type, Position pos, Towers tower, double burnDamage, int duration) 
        : TowerDecorator(type, pos, tower), burnDamagePerTick(burnDamage), burnDuration(duration) {}
    
    void shoot(Critter& critter) override {
        // Apply normal damage
        decoratedTower.shoot(critter);
        
        // Apply burning effect
        burningEnemies[&critter] = burnDuration;
        std::cout << "Enemy set on fire for " << burnDuration << " ticks!" << std::endl;
    }
    
    // This method should be called every game tick/update
    void updateBurningEffects() {
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

    double getBurnDamage() {return burnDamagePerTick;}
    double getBurnDuration() {return burnDuration;}
};

#endif // BURNING_EFFECT_DECORATOR_H