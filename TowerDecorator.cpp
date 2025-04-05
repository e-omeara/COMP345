#include "TowerDecorator.h"

using namespace std;

TowerDecorator::TowerDecorator(std::string type, Position pos, Towers tower)
: Towers(type, pos)
{
    
}

//overriden shoot method
void TowerDecorator::shoot(Critter &critter) { 
    Towers::shoot(critter); 
}

