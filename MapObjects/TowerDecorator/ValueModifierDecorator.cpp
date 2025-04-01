#include "ValueModifierDecorator.h"


ValueModifierDecorator::ValueModifierDecorator(std::string type, Position pos, Towers tower, double costMod, double refundMod, double rangeMod, double powerMod, double rofMod) 
: TowerDecorator(type, pos, tower), costModifier(costMod), refundModifier(refundMod), rangeModifier(rangeMod), powerModifier(powerMod), rofModifier(rofMod) 
{
    //new level up modifier
    double temp = 10000000.0;
    levelUp(temp);
    setBuyingCost(decoratedTower.getBuyingCost()+costMod);
    setRefundValue(decoratedTower.getRefundValue()+refundMod);
    setRange(decoratedTower.getRange()+rangeMod);
    setPower(decoratedTower.getPower()+powerMod);
    setRateOfFire(decoratedTower.getRateOfFire()-rofMod);
    
}

void ValueModifierDecorator::shoot(Critter &critter){
    Towers::shoot(critter);
}