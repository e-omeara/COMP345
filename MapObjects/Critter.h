#ifndef CRITTER_H
#define CRITTER_H

#include <iostream>
#include <vector>

//Struct for x, y coordinates
struct Position {
    int x, y;
};

//Critter class
class Critter {

//for all Critter types to access
protected:
    //Critter attributes
    int hp;
    int speed;
    int strength;
    int level;
    int reward;
    bool alive;

    //Tracks current position on the given path
    size_t positionIndex;  
    //Path for movement
    std::vector<Position> path;

public:
    //Constructor
    Critter(int hp, int spd, int str, int lvl, int reward, std::vector<Position> path);

    //Movement on the path for all critters
    //virtual void move();
    void move();
    
    //Taking damage (loss of hp)
    void takeDamage(int damage);
    
    //Getters
    bool isAlive() const;
    int getHP() const;
    int getStrength() const;
    int getSpeed() const;
    int getReward() const;  //Coins given when critter is killed
    int stealCoins() const; //Coins stolen from player if critter reaches end of the path
    bool hasReachedEnd() const;  //Check if critter reached the end of the path
    Position getPosition() const;
    //virtual std::string getType() const;
    std::string getType() const;

    //Setters
    void setHP(int health);
    void setStrength(int str);
    void setSpeed(int spd);


};

//Fast Critter (Moves Faster)
class FastCritter : public Critter {
public:
    FastCritter(std::vector<Position> path);
    void move();
    std::string getType() const;
};

//Tank Critter (More HP but Slower)
class TankCritter : public Critter {
public:
    TankCritter(std::vector<Position> path);
    std::string getType() const;
};

//Boss Critter (High HP and High Strength)
class BossCritter : public Critter {
public:
    BossCritter(std::vector<Position> path);
    std::string getType() const;
};

//CritterGroup class
class CritterGroup {

private:
    std::vector<Critter> critters;
    void generateWave(int waveLevel, std::vector<Position> path);

public:
    CritterGroup(int waveLevel, std::vector<Position> path);
    
    //Move all critters
    void moveCritters(int& playerCoins);

};

#endif
