// SlowingEffectDecorator.h
#ifndef SLOWING_EFFECT_DECORATOR_H
#define SLOWING_EFFECT_DECORATOR_H

#include "TowerDecorator.h"
#include <unordered_map>

// SlowingEffectDecorator reduces enemy movement speed
class SlowingEffectDecorator : public TowerDecorator {
private:
    double slowFactor; // How much to slow enemies (e.g., 0.5 = half speed)
    int slowDuration; // in game ticks
    
    // Track which critters are slowed and for how long
    std::unordered_map<Critter*, std::pair<int, double>> slowedEnemies; // duration, original speed

public:
    SlowingEffectDecorator(std::string type, Position pos, Towers tower, double slowAmount, int duration) ;
    
    void shoot(Critter& critter) override ;
    
    // This method should be called every game tick/update
    void updateSlowingEffects() ;

    double getSlowFactor() ;
    double getSlowDuration() ;
};

#endif // SLOWING_EFFECT_DECORATOR_H