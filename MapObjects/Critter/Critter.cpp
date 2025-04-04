#include "Critter.h"
#include "CritterObserver.h"

//Critter constructor, member initializer list since constant values 
Critter::Critter(int hp, int spd, int str, int lvl, int reward, std::vector<Position> path)
    : hp(hp), speed(spd), strength(str), level(lvl), reward(reward), path(path), positionIndex(0), alive(true) {}

//Critter takes damage, loss of hp
void Critter::takeDamage(int damage) {
    hp -= damage;
    if (hp <= 0) {
        alive = false;}
    notifyObservers();
}

//Check if critter is alive
bool Critter::isAlive() const {
    return alive;
}

//Get Position (Index) of critter
size_t Critter::getPositionIndex() const {
    return positionIndex;
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

//Get HP of Critter
int Critter::getHP() const { 
    return hp; 
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

//Get Critter Type
std::string Critter::getType() const { 
    return "Basic Critter"; 
}

//Setters
void Critter::setHP(int health){
    hp = health;
    notifyObservers();
}

void Critter::setStrength(int str){
    strength = str;
    notifyObservers();
}

void Critter::setSpeed(int spd){
    speed = spd;
    notifyObservers();
}

//Move the critter along the path
void Critter::move() {
    if (positionIndex + 1 < path.size()) {
        positionIndex += speed;
        if (positionIndex >= path.size()) {
            //To prevent going over
            positionIndex = path.size() - 1; 
        }
        //Notify observers of the move
        notifyObservers();
        //For Test Cases Only
        std::cout << "Critter moved to (" << path[positionIndex].x << ", " << path[positionIndex].y << ")\n";
    }
}

//FastCritter attributes(Moves Twice as Fast)
FastCritter::FastCritter(std::vector<Position> path) 
    : Critter(20, 1, 3, 1, 7, path) {}

void FastCritter::move() {
    positionIndex += (speed * 2);
    if (positionIndex >= path.size()) {
        positionIndex = path.size() - 1;
    }
    notifyObservers();
}

std::string FastCritter::getType() const { 
    return "Fast Critter"; 
}

//TankCritter attributes (More HP but Moves Slower)
TankCritter::TankCritter(std::vector<Position> path)
    : Critter(50, 1, 5, 1, 10, path) {}

std::string TankCritter::getType() const { 
    return "Tank Critter"; 
}

//BossCritter (High HP and High Strength)
BossCritter::BossCritter(std::vector<Position> path)
    : Critter(100, 1, 10, 1, 20, path) {}

std::string BossCritter::getType() const { 
    return "Boss Critter"; 
}

//CritterGroup constructor
CritterGroup::CritterGroup(int waveLevel, std::vector<Position> path) {
    generateWave(waveLevel, path);
}

std::vector<Critter> CritterGroup::getCritters(){
    return critters;
}

//Generate a wave of critters
void CritterGroup::generateWave(int waveLevel, std::vector<Position> path) {
    for (int i = 0; i < 3; ++i) critters.emplace_back(FastCritter(path));
    for (int i = 0; i < 3; ++i) critters.emplace_back(TankCritter(path));
    //Only one boss per wave
    critters.emplace_back(BossCritter(path));  
}

//Move all critters in the group
void CritterGroup::moveCritters(int& playerCoins) {
    for (auto& critter : critters) {
        if (critter.isAlive()) {
            if (critter.hasReachedEnd()) {
                //TODO: add player class and steal coins
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

//Observer adder
void Critter::addObserver(CritterObserver* observer) {
    observers.push_back(observer);
}

//Observer remover
void Critter::removeObserver(CritterObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

//Observer notifier
void Critter::notifyObservers() {
    for (auto observer : observers) {
        observer->update(*this);
    }
}


