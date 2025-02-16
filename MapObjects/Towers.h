#ifndef TOWER_H
#define TOWER_H

#include <string>
#include "Critter.h"
class Towers {
private:
    double level;
    double buyingCost;
    double refundValue;
    double range;
    double power;
    double rateOfFire;
    std::string type;
    Position position;
    Position origin;
    

public:
    // Constructor declaration
    Towers(double level, double cost, double refund, double towerRange, 
        double towerPower, double fireRate, std::string type, Position pos);
    

    // Constructor for type
    Towers(std::string type, Position pos);
    // Default position method
    static Position getOrigin(int x, int y);

    // base shoot method
    void shoot(Critter& critter);

    // level up method
    void levelUp(double& balance);

    // Getters
    double getBuyingCost() const;
    double getRefundValue() const;
    double getRange() const;
    double getPower() const;
    double getRateOfFire() const;
    double getLevel() const;

    // Setters
    void setBuyingCost(double cost);
    void setRefundValue(double refund);
    void setRange(double towerRange);
    void setPower(double towerPower);
    void setRateOfFire(double fireRate);
    void setLevel(double newLevel) ;
};

#endif