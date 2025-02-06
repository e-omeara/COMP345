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

private:
    //Critter attributes
    int hp;
    int speed;
    int strength;
    int level;
    int reward;
    bool alive = true;

    //Tracks current position on the given path
    size_t positionIndex;  
    //Path for movement
    std::vector<Position> path;

public:
    //Constructor
    Critter(int hp, int spd, int str, int lvl, int reward, std::vector<Position> path);

    //Movement on the path
    void move();
    
    //Taking damage (loss of hp)
    void takeDamage(int damage);
    
    //Getters
    bool isAlive() const;
    int getStrength() const;
    int getSpeed() const;
    int getReward() const;  //Coins given when critter is killed
    int stealCoins() const; //Coins stolen from player if critter reaches end of the path
    bool hasReachedEnd() const;  //Check if critter reached the end of the path
    Position getPosition() const;

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
