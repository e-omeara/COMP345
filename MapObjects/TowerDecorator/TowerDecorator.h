#ifndef TOWER_DECORATOR_H
#define TOWER_DECORATOR_H

#include "Towers.h"

class TowerDecorator : public Towers {
protected:
    Towers decoratedTower;

public:
    TowerDecorator(std::string type, Position pos, Towers tower);


    //virtual ~TowerDecorator() {};
    
    virtual void shoot(Critter& critter) ;
};

#endif // TOWER_DECORATOR_H