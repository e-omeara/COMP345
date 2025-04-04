#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <array> 
#include <vector>
#include <algorithm>
#include "Towers.h"
#include "TowerObserver.h"
#include "Critter.h"

//default constructor
TowerObserver::TowerObserver(Towers* tower) : tower(tower)
{
    //add observer to tower
    tower->addObserver(this);
    level = tower->getLevel();
    buyingCost = tower->getBuyingCost();
    refundValue = tower->getRefundValue();
    range = tower->getRange();
    power = tower->getPower();
    rateOfFire = tower->getRateOfFire();
}

//update function
void TowerObserver::update(double tlevel, double buyingCost, double refundValue, double trange, double tpower, double rateOfFire, Position tposition, string tType)
{
    //set new stats for the tower
    /* std::cerr << "Updated Tower View: " << std::endl <<
    "Level: " << tlevel <<  std::endl <<
    "BuyingCost " << buyingCost <<  std::endl <<
    "Refund Value " << refundValue <<  std::endl <<
    "Range: " << trange <<  std::endl <<
    "Power: " << tpower <<  std::endl <<
    "Rate Of Fire: " << rateOfFire <<  std::endl; */
    level = tlevel;
    TowerObserver::buyingCost = buyingCost;
    TowerObserver::refundValue = refundValue;
    range = trange;
    power = tpower;
    TowerObserver::rateOfFire = rateOfFire;

}
//getter methods
Position TowerObserver::getPosition(){
    return position;
}

string TowerObserver::getType(){
    return type;
}

int TowerObserver::getRange(){
    return range;
}

int TowerObserver::getLevel(){
    return level;
}

int TowerObserver::getPower(){
    return power;
}

int TowerObserver::getBuyingCost(){
    return buyingCost;
}

int TowerObserver::getRefundValue(){
    return refundValue;
}

int TowerObserver::getRateOfFire(){
    return rateOfFire;
}

void TowerObserver::setBuyingCost(double cost) { buyingCost = cost;}
void TowerObserver::setRefundValue(double refund) { refundValue = refund;  }
void TowerObserver::setRange(double towerRange) { range = towerRange;  }
void TowerObserver::setPower(double towerPower) { power = towerPower;  }
void TowerObserver::setRateOfFire(double fireRate) { rateOfFire = fireRate; }
void TowerObserver::setLevel(double newLevel) { level = newLevel; }