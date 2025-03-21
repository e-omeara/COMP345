#ifndef TOWER_DECORATOR_H
#define TOWER_DECORATOR_H

#include "Towers.h"

class TowerDecorator : public Towers {
protected:
    Towers decoratedTower;

public:
    TowerDecorator(std::string type, Position pos, Towers tower)
        : Towers(type, pos), decoratedTower(tower) {}
    virtual ~TowerDecorator() {}
    
    void shoot(Critter& critter) override { decoratedTower.shoot(critter); }
};

#endif // TOWER_DECORATOR_H