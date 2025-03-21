#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <array> 
#include <vector>
#include <algorithm>
#include <cmath>
#include "Towers.h"
#include "TowerObserver.h"
#include "Critter.h"



//Default Constructor




Towers::Towers(double level, double cost, double refund, double towerRange, 
    double towerPower, double fireRate, std::string type, Position pos, char targType)

    : level(level)
    , buyingCost(cost)
    , refundValue(refund)
    , range(towerRange)
    , power(towerPower)
    , rateOfFire(fireRate)
    , type(type)
    , position(pos)
    , targetingType(targType)
{}

//Constructor to make defined tower types
//Use this one for driver
Towers::Towers(std::string type, Position pos)
    : type(type)
    , position(pos)
{
    level = 1;
    if(type == "archer")
    {
        //std::cout << "Archer " << std::endl;
        buyingCost = 10;
        refundValue = 3;
        range = 3;
        power = 1;
        rateOfFire = 500; //milliseconds
        targetingType = 'e';
    }
    else if(type == "ballista")
    {
        //std::cout << "ballista " << std::endl;
        buyingCost = 20;
        refundValue = 6;
        range = 7;
        power = 5;
        rateOfFire = 1000; //milliseconds
        targetingType = 's';
    }
    else if(type == "catapult")
    {
        //std::cout << "catapult " << std::endl;
        buyingCost = 30;
        refundValue = 10;
        range = 5;
        power = 10;
        rateOfFire = 1200; //milliseconds
        targetingType = 'w';
    }
    else
    {
        //defaults to archer, but shoots near
        buyingCost = 10;
        refundValue = 3;
        range = 3;
        power = 1;
        rateOfFire = 500; //milliseconds
        targetingType = 'n';
    }
}

//Constructor for type and custom targeting method
Towers::Towers(std::string type, Position pos, char targType)
    : type(type)
    , position(pos)
    , targetingType(targType)
{
    level = 1;
    if(type == "archer")
    {
        //std::cout << "Archer " << std::endl;
        buyingCost = 10;
        refundValue = 3;
        range = 3;
        power = 1;
        rateOfFire = 500; //milliseconds
    }
    else if(type == "ballista")
    {
        //std::cout << "ballista " << std::endl;
        buyingCost = 20;
        refundValue = 6;
        range = 7;
        power = 5;
        rateOfFire = 1000; //milliseconds
    }
    else if(type == "catapult")
    {
        //std::cout << "catapult " << std::endl;
        buyingCost = 30;
        refundValue = 10;
        range = 5;
        power = 10;
        rateOfFire = 1200; //milliseconds
    }
    else
    {
        //defaults to archer, but shoots near
        buyingCost = 10;
        refundValue = 3;
        range = 3;
        power = 1;
        rateOfFire = 500; //milliseconds
    }
}
//Method to get the origin position
Position Towers::getOrigin(int x = 0, int y = 0){
    Position origin;
    origin.x = x;
    origin.y = y;
    return origin;

}


//deprecated code:
//used before findTarget() rework
//associated attribute was vector<int> fireZone
/*******************************************
//finds which section of path is within range. sets fire zone to a vector of position indeces
void Towers::findFireZone(const std::vector<Position>& path){
    fireZone.clear();
    Position p;
    //clunky solution. grows at n*k; n=size of path, k = range. could implement with quicksort instead to make this faster
    if(targetingType == 'n'){//prioritizing being close to tower
        for(int i = 1; i <=2*range; i++){
            for(int index = path.size()-1; index>=0; index--){
                p = path[index];
                //if x,y distance isn't > range, then push if x distance + y distance = i.
                if((abs(p.x-position.x)<=range && abs(p.y-position.y)<=range) && ((abs(p.x-position.x) + abs(p.y-position.y))==i)){
                    fireZone.push_back(index);
                }
            }
        }
    }
    else{//prioritizing being close to exit
        for(int index = path.size()-1; index>=0; index--){
            p = path[index];
            if(abs(p.x-position.x)<=range && abs(p.y-position.y)<=range){
                fireZone.push_back(index);
            }
        }
    }
}
*******************************************/

//determines if a critter is in range -- made this function inline
/*bool Towers::isInRange(Critter* critter) const{
    return (abs(critter->getPosition().x - position.x)) <= range && (abs(critter->getPosition().y - position.y) <= range);
}*/

// returns the pointer to the highest priority critter. uses fireZone attribute
Critter* Towers::findTarget(const std::vector<Critter*>& activeCritters) const {
    if(activeCritters.size() == 0)
        return nullptr; //can't target a critter if none in play
    switch (targetingType){
        case 'e':{
            //exit
            Critter* closestToExit = activeCritters[0];
            for(Critter* critter : activeCritters){
                if(isInRange(critter) && (critter->getPositionIndex() > closestToExit->getPositionIndex())){
                    closestToExit = critter;
                }
            }
            return closestToExit;
            break;
        }
        case 'n':{//near
                Critter* nearestCritter = activeCritters[0];
                for(Critter* critter : activeCritters){
                    if(isInRange(critter)){
                        //now checking if it's closer than nearest
                        if((abs(critter->getPosition().x - position.x)) + //not really finding distance but it's fine...
                        (abs(critter->getPosition().y - position.y)) < //is the x distance + y distance less than
                        ((abs(nearestCritter->getPosition().x - position.x)) + //the nearest critter's x + y distance?
                        (abs(nearestCritter->getPosition().y - position.y)))){
                            nearestCritter = critter;
                        }
                    }
                    
                }
            return nearestCritter;
            break;
        }
        case 's':{//strong
                return findStrongTarget(activeCritters);
            break;
        }
        case 'w':{//weak
            return findWeakTarget(activeCritters);
            break;
        }
        default:{//invalid / no targ type
            cerr << "invalid targeting type";
            return nullptr;
            break;
        }
    }
    return nullptr; //no valid critter found      
}

// returns the pointer to the least strong critter in range
Critter* Towers::findWeakTarget(const std::vector<Critter*>& activeCritters) const {
    if(activeCritters.size() > 0){
        Critter* weakest = activeCritters[0];
        for(Critter* critter : activeCritters){
            if(isInRange(critter) && critter->getStrength() < weakest->getStrength()){
                weakest = critter;
            }
        }
        return weakest;
    }
    return nullptr; //no valid critter found
}
// returns the pointer to the strongest critter in range
Critter* Towers::findStrongTarget(const std::vector<Critter*>& activeCritters) const {
    if(activeCritters.size() > 0){
        Critter* strongest = activeCritters[0];
        for(Critter* critter : activeCritters){
            if(isInRange(critter) && critter->getStrength() > strongest->getStrength()){
                strongest = critter;
            }
        }
        return strongest;
    }
    return nullptr; //no valid critter found
}

//recursive shoot method that allows for variable sized parameter
//parameter size >1 mostly for catapult allowing to hit more enemies
//Critter will not get hit if it is out of range
void Towers::shoot(Critter& critter) 
{
    //std::cout << std::abs(critter.getPosition().x - position.x) << std::endl;
    //std::cout << std::abs(critter.getPosition().y - position.y) << std::endl;
    //std::cout << range << std::endl;
    //std::cout << (std::abs(critter.getPosition().x - position.x) < range) << std::endl;
    if(isInRange(&critter))
    {
        critter.setHP(critter.getHP()-power);
        std::cout << "Hit!" << std::endl;
    }
    else
    {
        std::cout << "Out of Range!" << std::endl;
    }
}


//level up method where balance is the player's gold balance
void Towers::levelUp(double& balance)
{
    level += 1;
    balance -= buyingCost;
    //shoots faster
    if(type.compare("archer"))
    {
        refundValue += 4;
        power += 1;
        if(level == 2 || level == 3)
        {
            rateOfFire -= 100;
        }
    }
    //more power
    else if(type.compare("ballista"))
    {
        refundValue += 8;
        power += 5;
    }
    //more power + hits more critters
    else if(type.compare("catapult"))
    {
        refundValue += 10;
        power += 5;
    }

    notifyObservers();
}

void Towers::addObserver(TowerObserver* observer)
{
    observers.push_back(observer);
    notifyObservers();
}

void Towers::removeObserver(TowerObserver* observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Towers::notifyObservers() {
    for (TowerObserver* observer : observers) {
        observer->update(level, buyingCost, refundValue, range, power, rateOfFire, position, type, targetingType);
    }
}



// Getters
double Towers::getBuyingCost() const { return buyingCost; }
double Towers::getRefundValue() const { return refundValue; }
double Towers::getRange() const { return range; }
double Towers::getPower() const { return power; }
double Towers::getRateOfFire() const { return rateOfFire; }
double Towers::getLevel() const { return level; }
char Towers::getTargetingType() const {return targetingType;}

// Setters
void Towers::setBuyingCost(double cost) { buyingCost = cost; notifyObservers(); }
void Towers::setRefundValue(double refund) { refundValue = refund; notifyObservers(); }
void Towers::setRange(double towerRange) { range = towerRange; notifyObservers(); }
void Towers::setPower(double towerPower) { power = towerPower; notifyObservers(); }
void Towers::setRateOfFire(double fireRate) { rateOfFire = fireRate; notifyObservers(); }
void Towers::setLevel(double newLevel) { level = newLevel; notifyObservers(); }
void Towers::setTargetingType(char targType) {targetingType = targType; notifyObservers(); }


//std::vector<int> Towers::getFireZone() const {return fireZone;}
//void Towers::setFireZone(std::vector<int> fZone) {fireZone = fZone; notifyObservers();}

