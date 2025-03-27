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
    std::string type;
    char targetingType;
    Position position;
    std::vector<TowerObserver*> observers;

protected:
    // returns if critter pointer param is in range of tower object
    inline bool isInRange(Critter* critter) const 
    {return (abs(critter->getPosition().x - position.x) <= range) 
         && (abs(critter->getPosition().y - position.y) <= range);};
    
    //deprecated code
    // sets fireZone to the section of the path that is in range in descending order of priority. Only called on creation or movement
    // void findFireZone(const std::vector<Position>& path); //prioritizes being close to the exit, unless targ type is near

public:
    // Constructor declaration
    Towers(double level = 0.0, double cost = 0.0, double refund = 0.0, double towerRange = 0.0, 
        double towerPower = 0.0, double fireRate = 0.0, std::string type = "N/A", 
        Position pos = getOrigin(0,0), char targetingType = '0');

    // Constructor for type
    Towers(std::string type, Position position);

    // Constructor for type
    Towers(std::string type, Position position, char targType);
    // Default position method
    static Position getOrigin(int x, int y);

    // base shoot method
    virtual void shoot(Critter& critter);

    // level up method
    void levelUp(double& balance);


    //inline bool isInRange(Critter* critter) const 
    //{return (abs(critter->getPosition().x - position.x) <= range) 
    //     && (abs(critter->getPosition().y - position.y) <= range);};


    //findTarget() calls findWeakTarget() or findStrongTarget() for weak and strong targeting types, respectively
    Critter* findTarget(const std::vector<Critter*>& activeCritters) const; //returns first critter according to priority. used by both exit and near
    
    //normally shouldn't be manually called. findTarget() will determine the appropriate method.
    Critter* findWeakTarget(const std::vector<Critter*>& activeCritters) const; //returns weakest critter in range
    Critter* findStrongTarget(const std::vector<Critter*>& activeCritters) const; //returns strongest critter

    void addObserver(TowerObserver* observer);

    void removeObserver(TowerObserver* observer);

    void notifyObservers();

    // Getters
    virtual double getBuyingCost() const;
    virtual double getRefundValue() const;
    virtual double getRange() const;
    virtual double getPower() const;
    virtual double getRateOfFire() const;
    virtual double getLevel() const;
    virtual char getTargetingType() const;


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