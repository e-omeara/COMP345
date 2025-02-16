#ifndef TOWER_H
#define TOWER_H

#include <string>
#include "Enemy.h"

class Towers {
private:
    double level;
    double buyingCost;
    double refundValue;
    double range;
    double power;
    double rateOfFire;
    std::string type;

public:
    // Constructor declaration
    Towers(double level = 0.0, double cost = 0.0, double refund = 0.0, double towerRange = 0.0, 
         double towerPower = 0.0, double fireRate = 0.0);

    Towers(std::string type = "archer");

    template <typename... Args>
    void shoot(Enemy first, Args... rest) {}

    void shoot() {}

    void levelUp(double level = 1.0) {}

    // Getters
    double getBuyingCost() const;
    double getRefundValue() const;
    double getRange() const;
    double getPower() const;
    double getRateOfFire() const;

    // Setters
    void setBuyingCost(double cost);
    void setRefundValue(double refund);
    void setRange(double towerRange);
    void setPower(double towerPower);
    void setRateOfFire(double fireRate);
};

#endif