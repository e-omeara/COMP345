#include "ValueModifierDecorator.h"


ValueModifierDecorator::ValueModifierDecorator(std::string type, Position pos, Towers tower, double costMod, double refundMod, double rangeMod, double powerMod, double rofMod) 
: TowerDecorator(type, pos, tower), costModifier(costMod), refundModifier(refundMod), rangeModifier(rangeMod), powerModifier(powerMod), rofModifier(rofMod) 
{
    //new level up modifier
    level += 1;
    buyingCost += costMod;
    refundValue += refundMod;
    range += rangeMod;
    power += powerMod;
    rateOfFire -= rofMod;
}

void ValueModifierDecorator::shoot(Critter &critter){
    Towers::shoot(critter);
}