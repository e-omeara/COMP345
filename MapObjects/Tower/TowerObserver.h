#ifndef TOWER_OBS
#define TOWER_OBS

#include <string>
#include <vector>
#include <algorithm>
#include "Critter.h"
#include "Towers.h"

using namespace std;


class TowerObserver
{
    private:
        Towers& tower;
        double level;
        double buyingCost;
        double refundValue;
        double power;
        double range;
        

        string type;
        Position position;

    public:
        TowerObserver(Towers& tower);

        void update(double tlevel = 0, double buyingCost = 0, double refundValue = 0, double trange = 0, double tpower = 0, double rateOfFire = 0, Position tposition = {0,0}, string tType = "normal", string targetingType = "exit");

        Position getPosition();

        string getType();

        int getRange();

        int getLevel();

        int getPower();

    };


#endif