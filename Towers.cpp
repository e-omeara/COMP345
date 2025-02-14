#include "Towers.h"
#include <string>
#include <thread>
#include <chrono>
#include <atomic>

// Constructor
Towers::Towers(double level, double cost, double refund, double towerRange, 
            double towerPower, double fireRate)

    : level(level)
    , buyingCost(cost)
    , refundValue(refund)
    , range(towerRange)
    , power(towerPower)
    , rateOfFire(fireRate)
{}

Towers::Towers(std::string type)
    : type(type)
{
    if(type.compare("archer"))
    {
        buyingCost = 10;
        refundValue = 3;
        range = 3;
        power = 1;
        rateOfFire = 500; //milliseconds
    }
    else if(type.compare("ballista"))
    {
        buyingCost = 20;
        refundValue = 6;
        range = 7;
        power = 5;
        rateOfFire = 1000; //milliseconds
    }
    else if(type.compare("catapult"))
    {
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

//recursive method to shoot multiple enemy (mostly for catapult)
template <typename... Args>
void shoot(Enemy first, Args... rest) 
{
    first.hp -= power;
    if(type.compare("ballista"))
    {
        first.speed -= 2;

        std::thread([this]() {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            speed++;
            std::cout << name << " has recovered! Speed: " << speed << std::endl;
        }).detach();  // Detach so it runs independently
    }
    shoot(rest...);
}

void levelUp() {  }

// Getters
double Towers::getBuyingCost() const { return buyingCost; }
double Towers::getRefundValue() const { return refundValue; }
double Towers::getRange() const { return range; }
double Towers::getPower() const { return power; }
double Towers::getRateOfFire() const { return rateOfFire; }

// Setters
void Towers::setBuyingCost(double cost) { buyingCost = cost; }
void Towers::setRefundValue(double refund) { refundValue = refund; }
void Towers::setRange(double towerRange) { range = towerRange; }
void Towers::setPower(double towerPower) { power = towerPower; }
void Towers::setRateOfFire(double fireRate) { rateOfFire = fireRate; }

