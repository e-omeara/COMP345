#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <array> 
#include <vector>
#include <algorithm>
#include "Towers.h"
#include "Critter.h"

TowerObserver::TowerObserver(Towers& tower) : tower(tower)
{
    tower.addObserver(this);
}

void TowerObserver::update(double level, double buyingCost, double refundValue, double range, double power, double rateOfFire, Position position)
{
    std::cout << "Updated Tower View: " << std::endl <<
    "Level: " << level <<  std::endl <<
    "BuyingCost " << buyingCost <<  std::endl <<
    "Refund Value " << refundValue <<  std::endl <<
    "Range: " << range <<  std::endl <<
    "Power: " << power <<  std::endl <<
    "Rate Of Fire: " << rateOfFire <<  std::endl;
}

//Default Constructor




Towers::Towers(double level, double cost, double refund, double towerRange, 
    double towerPower, double fireRate, std::string type, Position pos)

    : level(level)
    , buyingCost(cost)
    , refundValue(refund)
    , range(towerRange)
    , power(towerPower)
    , rateOfFire(fireRate)
    , type(type)
    , position(pos)
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
        //defaults to archer
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


//recursive shoot method that allows for variable sized parameter
//parameter size >1 mostly for catapult allowing to hit more enemies
//Critter will not get hit if it is out of range
void Towers::shoot(Critter& critter) 
{
    //std::cout << std::abs(critter.getPosition().x - position.x) << std::endl;
    //std::cout << std::abs(critter.getPosition().y - position.y) << std::endl;
    //std::cout << range << std::endl;
    //std::cout << (std::abs(critter.getPosition().x - position.x) < range) << std::endl;
    if(std::abs(critter.getPosition().x - position.x) < range || std::abs(critter.getPosition().y - position.y) < range)
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
}

void Towers::removeObserver(TowerObserver* observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Towers::notifyObservers() {
    for (TowerObserver* observer : observers) {
        observer->update(level, buyingCost, refundValue, range, power, rateOfFire, position);
    }
}

// Getters
double Towers::getBuyingCost() const { return buyingCost; }
double Towers::getRefundValue() const { return refundValue; }
double Towers::getRange() const { return range; }
double Towers::getPower() const { return power; }
double Towers::getRateOfFire() const { return rateOfFire; }
double Towers::getLevel() const { return level; }

// Setters
void Towers::setBuyingCost(double cost) { buyingCost = cost; notifyObservers(); }
void Towers::setRefundValue(double refund) { refundValue = refund; notifyObservers(); }
void Towers::setRange(double towerRange) { range = towerRange; notifyObservers(); }
void Towers::setPower(double towerPower) { power = towerPower; notifyObservers(); }
void Towers::setRateOfFire(double fireRate) { rateOfFire = fireRate; notifyObservers(); }
void Towers::setLevel(double newLevel) { level = newLevel; notifyObservers(); }
