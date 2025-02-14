#include <iostream>
#include <string>

class Enemy{
    private:
        double hp;
        double speed;

    public:
        Enemy(int hp, double speed) 
            : hp(hp) 
            , speed(speed)
            {}
};


