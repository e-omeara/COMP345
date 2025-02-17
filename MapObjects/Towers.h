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
    Towers(double level = 0.0, double cost = 0.0, double refund = 0.0, double towerRange = 0.0, 
        double towerPower = 0.0, double fireRate = 0.0, std::string type = "N/A", Position pos = getOrigin(0,0));
    

    // Constructor for type
    Towers(std::string type, Position position);
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