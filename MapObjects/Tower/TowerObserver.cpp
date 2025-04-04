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
TowerObserver::TowerObserver(Towers& thetower) {
    //add observer to tower
    thetower.addObserver(this);
}

TowerObserver::TowerObserver(Towers* thetower) {
    //add observer to tower
    thetower->addObserver(this);
}

//update function
void TowerObserver::update(double tlevel, double buyingCost, double refundValue, double trange, double tpower, double rateOfFire, Position tposition, string tType, char targType)
{
    //set new stats for the tower
    std::cerr << "Updated Tower View: " << std::endl <<
    "Level: " << tlevel <<  std::endl <<
    "BuyingCost " << buyingCost <<  std::endl <<
    "Refund Value " << refundValue <<  std::endl <<
    "Range: " << trange <<  std::endl <<
    "Power: " << tpower <<  std::endl <<
    "Rate Of Fire: " << rateOfFire <<  std::endl <<
    "Targting Type: " << targType << std::endl;
    position = tposition;
    type = tType; // tower type
    power = tpower;
    range = trange;
    level = tlevel;
    targetingType =  targType; // tower targeting strategy/type
}
//getter methods
Position TowerObserver::getPosition(){
    return position;
}

string TowerObserver::getType(){
    return type;


}

char TowerObserver::getTargetingType(){
    return targetingType;
}

int TowerObserver::getRange(){
    return int(range);
}

int TowerObserver::getLevel(){
    return int(level);
}

int TowerObserver::getPower(){
    return int(power);
}
