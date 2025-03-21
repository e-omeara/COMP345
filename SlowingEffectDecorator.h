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
    SlowingEffectDecorator(std::string type, Position pos, Towers tower, double slowAmount, int duration) 
        : TowerDecorator(type, pos, tower), slowFactor(slowAmount), slowDuration(duration) {}
    
    void shoot(Critter& critter) override {
        // Apply normal damage
        decoratedTower.shoot(critter);
        
        // Apply slowing effect
        double originalSpeed = critter.getSpeed();
        
        // Only apply if not already slowed
        if (slowedEnemies.find(&critter) == slowedEnemies.end()) {
            // Store original speed and duration
            slowedEnemies[&critter] = std::make_pair(slowDuration, originalSpeed);
            
            // Apply slow
            critter.setSpeed(originalSpeed * slowFactor);
            std::cout << "Enemy slowed by " << (1.0 - slowFactor) * 100 << "% for " << slowDuration << " ticks!" << std::endl;
        } else {
            // Reset duration if already slowed
            slowedEnemies[&critter].first = slowDuration;
        }
    }
    
    // This method should be called every game tick/update
    void updateSlowingEffects() {
        auto it = slowedEnemies.begin();
        while (it != slowedEnemies.end()) {
            Critter* critter = it->first;
            int& remainingDuration = it->second.first;
            double originalSpeed = it->second.second;
            
            // Decrease duration
            remainingDuration--;
            
            // Remove if duration expired, restore original speed
            if (remainingDuration <= 0) {
                critter->setSpeed(originalSpeed);
                std::cout << "Slow effect expired, speed restored to " << originalSpeed << std::endl;
                it = slowedEnemies.erase(it);
            } else {
                ++it;
            }
        }
    }

    double getSlowFactor() {return slowFactor;}
    double getSlowDuration() {return slowDuration;}
};

#endif // SLOWING_EFFECT_DECORATOR_H