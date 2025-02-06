#include "Critter.h"

//Critter constructor, member initializer list since constant values 
Critter::Critter(int hp, int spd, int str, int lvl, int reward, std::vector<Position> path)
    : hp(hp), speed(spd), strength(str), level(lvl), reward(reward), path(path), positionIndex(0) {}

//Critter takes damage, loss of hp
void Critter::takeDamage(int damage) {
    hp -= damage;
    if (hp <= 0) alive = false;
}

//Check if critter is alive
bool Critter::isAlive() const {
    return alive;
}

//Get reward when critter is slain
int Critter::getReward() const {
    return reward;
}

//Return the amount of coins stolen if the critter reaches the end of the path
int Critter::stealCoins() const {
    return strength;
}

//Check if the critter has reached the end of the path
bool Critter::hasReachedEnd() const {
    return positionIndex == path.size() - 1;
}


//Get strength value
int Critter::getStrength() const {
    return strength;
}

//Get speed value
int Critter::getSpeed() const {
    return speed;
}

//Get current critter position
Position Critter::getPosition() const {
    return path[positionIndex];
}

//Move the critter along the path
void Critter::move() {
    if (positionIndex + 1 < path.size()) {
        positionIndex += speed;
        if (positionIndex >= path.size()) {
            //To prevent going over
            positionIndex = path.size() - 1; 
        }
        //For Test Cases Only
        std::cout << "Critter moved to (" << path[positionIndex].x << ", " << path[positionIndex].y << ")\n";
    }
}

//CritterGroup constructor
CritterGroup::CritterGroup(int waveLevel, std::vector<Position> path) {
    generateWave(waveLevel, path);
}

//Generate a wave of critters
void CritterGroup::generateWave(int waveLevel, std::vector<Position> path) {
    int baseHP = 10 + waveLevel * 5;
    int baseSpeed = 1 + waveLevel / 2;
    int baseStrength = 2 + waveLevel;
    int baseReward = 5 + waveLevel * 2;
    
    for (int i = 0; i < 5 + waveLevel; ++i) {
        critters.push_back(Critter(baseHP, baseSpeed, baseStrength, waveLevel, baseReward, path));
    }
}

//Move all critters in the group
void CritterGroup::moveCritters(int& playerCoins) {
    for (auto& critter : critters) {
        if (critter.isAlive()) {
            if (critter.hasReachedEnd()) {
                playerCoins -= critter.stealCoins();
                //Test Case
                std::cout << "Critter reached the exit! Player lost " << critter.stealCoins() << " coins!\n";
            } else {
                critter.move();
            }
          //if critter is slain, give player reward (coins)  
        } else { 
            playerCoins += critter.getReward();
            //Test Case
            std::cout << "Critter killed! Player earned " << critter.getReward() << " coins!\n";
        }
    }
}
