#ifndef TOWER_OBS
#define TOWER_OBS

#include <string>
#include <vector>
#include <algorithm>
#include "Critter.h"
#include "Towers.h"




class TowerObserver
{
    private:
        Towers& tower;

    public:
        TowerObserver(Towers& tower);

        void update(double level = 0, double buyingCost = 0, double refundValue = 0, double range = 0, double power = 0, double rateOfFire = 0, Position position = {0,0});
};


#endif