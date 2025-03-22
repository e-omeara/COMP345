#include "SlowingEffectDecorator.h"



using namespace std;



SlowingEffectDecorator::SlowingEffectDecorator(std::string type, Position pos, Towers tower, double slowAmount, int duration) 
        : TowerDecorator(type, pos, tower), slowFactor(slowAmount), slowDuration(duration) {


        }


void SlowingEffectDecorator::shoot(Critter &critter){
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


void SlowingEffectDecorator::updateSlowingEffects() {
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

//getter methods
double SlowingEffectDecorator::getSlowFactor(){
    return slowFactor;
}


double SlowingEffectDecorator::getSlowDuration() {
    return slowDuration;
}