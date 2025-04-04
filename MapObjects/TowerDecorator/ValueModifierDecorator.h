#ifndef VALUE_MODIFIER_DECORATOR_H
#define VALUE_MODIFIER_DECORATOR_H

#include "TowerDecorator.cpp"
#include "TowerObserver.cpp"

// ValueModifierDecorator changes Tower attributes
class ValueModifierDecorator : public TowerDecorator {
private:
    double costModifier;
    double refundModifier;
    double rangeModifier;
    double powerModifier;
    double rofModifier;

public:
ValueModifierDecorator(std::string type, Position pos, Towers tower, double costMod, double refundMod, double rangeMod, double powerMod, double rofMod);

void shoot(Critter &critter){

}

};

#endif // VALUE_MODIFIER_DECORATOR_H