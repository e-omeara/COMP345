#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include <algorithm>
#include "Critter.h"
#include "Map.h"
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
    char targetingType;
    std::string type;
    Position position;
    std::vector<TowerObserver*> observers;
    std::vector<int> fireZone;

protected:
    inline bool isInRange(Critter* critter) const 
    {return (abs(critter->getPosition().x - position.x) <= range) 
         && (abs(critter->getPosition().y - position.y) <= range);};
    
    // sets fireZone to the section of the path that is in range in descending order of priority. Only called on creation or movement
    void findFireZone(const std::vector<Position>& path); //prioritizes being close to the exit, unless targ type is near

public:
    // Constructor declaration
    Towers(double level = 0.0, double cost = 0.0, double refund = 0.0, double towerRange = 0.0, 
        double towerPower = 0.0, double fireRate = 0.0, std::string type = "N/A", 
        Position pos = getOrigin(0,0), char targetingType = '0');

    // Constructor for type
    Towers(std::string type, Position position);

    // Constructor for type & custom targeting method
    Towers(std::string type, Position position, char targetingType);

    // Default position method
    static Position getOrigin(int x, int y);

    // base shoot method
    void shoot(Critter& critter);

    // level up method
    void levelUp(double& balance);

    void addObserver(TowerObserver* observer);

    void removeObserver(TowerObserver* observer);

    void notifyObservers();

    // returns a critter pointer for shooting. uses fireZone attribute. returns a null pointer on failure
    //only call if activeCritters size > 0
    Critter* findTarget(const std::vector<Critter*>& activeCritters) const; //returns first critter according to priority. used by both exit and near
    Critter* findWeakTarget(const std::vector<Critter*>& activeCritters) const; //returns weakest critter in range
    Critter* findStrongTarget(const std::vector<Critter*>& activeCritters) const; //returns strongest critter


    // Getters
    double getBuyingCost() const;
    double getRefundValue() const;
    double getRange() const;
    double getPower() const;
    double getRateOfFire() const;
    double getLevel() const;
    char getTargetingType() const;
    std::vector<int> getFireZone() const;

    // Setters
    void setBuyingCost(double cost);
    void setRefundValue(double refund);
    void setRange(double towerRange);
    void setPower(double towerPower);
    void setRateOfFire(double fireRate);
    void setLevel(double newLevel) ;
    void setTargetingType(char targetType);
    void setFireZone(std::vector<int>); //used in rare cases when setting fire zone manually. should normally use rangeFinder
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