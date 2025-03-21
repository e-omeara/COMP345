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




TowerObserver::TowerObserver(Towers& tower) : tower(tower)
{
    tower.addObserver(this);
}

void TowerObserver::update(double tlevel, double buyingCost, double refundValue, double trange, double tpower, double rateOfFire, Position tposition, string tType, char targetingType)
{
    std::cout << "Updated Tower View: " << std::endl <<
    "Level: " << tlevel <<  std::endl <<
    "BuyingCost " << buyingCost <<  std::endl <<
    "Refund Value " << refundValue <<  std::endl <<
    "Range: " << trange <<  std::endl <<
    "Power: " << tpower <<  std::endl <<
    "Rate Of Fire: " << rateOfFire <<  std::endl;
    position = tposition;
    type = tType;
    power = tpower;
    range = trange;
    level = tlevel;
}

Position TowerObserver::getPosition(){
    return position;
}

string TowerObserver::getType(){
    return type;


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
