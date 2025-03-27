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
    BurningEffectDecorator(std::string type, Position pos, Towers tower, double burnDamage, int duration);
    
    void shoot(Critter& critter) override ;
    
    // This method should be called every game tick/update
    void updateBurningEffects() ;

    double getBurnDamage();
    double getBurnDuration();
};

#endif // BURNING_EFFECT_DECORATOR_H