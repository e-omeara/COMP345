#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include <algorithm>
#include "Critter.h"
//#include "TowerObserver.h"

class TowerObserver;

class Towers {
private:
    double level;
    double buyingCost;
    double refundValue;
    double range;
    double power;
    double rateOfFire;
    std::string targetingType;
    std::string type;
    Position position;
    std::vector<TowerObserver*> observers;

public:
    // Constructor declaration
    Towers(double level = 0.0, double cost = 0.0, double refund = 0.0, double towerRange = 0.0, 
        double towerPower = 0.0, double fireRate = 0.0, std::string type = "N/A", 
        Position pos = getOrigin(0,0), std::string targetingType = "N/A");
    

    // Constructor for type
    Towers(std::string type, Position position);

    // Constructor for type & custom targeting method
    Towers(std::string type, Position position, std::string targetingType);

    // Default position method
    static Position getOrigin(int x, int y);

    // base shoot method
    void shoot(Critter& critter);

    // level up method
    void levelUp(double& balance);

    void addObserver(TowerObserver* observer);

    void removeObserver(TowerObserver* observer);

    void notifyObservers();

    //Return the section of the path that is in range, in descending order of priority
    std::vector<int> standardRangeFinder(); //prioritizes being close to the exit. used by exit, weak, strong
    std::vector<int> nearRangeFinder(); //prioritizes being near to the tower. used by near

    //returns a critter for shooting
    Critter findTarget(); //returns first critter according to priority. used by both exit and near
    Critter findWeakTarget(); //returns weakest critter in range
    Critter findStrongTarget(); //returns strongest critter


    // Getters
    double getBuyingCost() const;
    double getRefundValue() const;
    double getRange() const;
    double getPower() const;
    double getRateOfFire() const;
    double getLevel() const;
    std::string getTargetingType() const;

    // Setters
    void setBuyingCost(double cost);
    void setRefundValue(double refund);
    void setRange(double towerRange);
    void setPower(double towerPower);
    void setRateOfFire(double fireRate);
    void setLevel(double newLevel) ;
    void setTargetingType(std::string targetType);
};


/*
class TowerObserver
{
    private:
        Towers& tower;

    public:
        TowerObserver(Towers& tower);

        void update(double level = 0, double buyingCost = 0, double refundValue = 0, double range = 0, double power = 0, double rateOfFire = 0, Position position = {0,0});
};
*/

#endif // TOWERS_H