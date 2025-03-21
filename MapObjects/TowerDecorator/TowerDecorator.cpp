#include "TowerDecorator.h"

using namespace std;



TowerDecorator::TowerDecorator(std::string type, Position pos, Towers tower)
: Towers(type, pos), decoratedTower(tower) {}

void TowerDecorator::shoot(Critter &critter) { 
    decoratedTower.shoot(critter); 
}

