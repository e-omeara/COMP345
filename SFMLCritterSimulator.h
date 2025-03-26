#ifndef SFMLCRITTERSIMULATOR_H
#define SFMLCRITTERSIMULATOR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Critter.h"
#include "Map.h"
#include "CritterFactory.h"

class SFMLCritterSimulator {

public:

    //Construct with the made map and the path
    SFMLCritterSimulator(Map* map, const std::vector<Position>& path);

    //Run the critter simulation loop
    void runSimulation(sf::RenderWindow window);
    //check the clock and update the critters as necessary
    float checkClock(float elapsedTime, sf::Clock* simulationClock);
    //Draw the map background (for visual clarity) and all active critters with health bars and tooltips.
    void drawSimulation(sf::RenderWindow* theWindow);
    //Check if the current wave is finished and load the next wave.
    void checkAndLoadNextWave(sf::RenderWindow* theWindow);

    std::vector<Critter*> getCritters();

    //Wave control functions
    bool isWaveComplete() const;
    void startNextWave();

    //Accumulated rewards/damage
    int coinsRewarded;
    int healthLost;

    //Update active critters (move them along the path) and update their sprite positions
    void updateCritters(float dt);

private:

    Map* map;                    
    std::vector<Position> path;   //The path extracted from the map

    //sf::RenderWindow window;
    sf::Texture fastTexture, tankTexture, bossTexture;
    sf::Font font;
    
    
    //Active critters currently moving and their sprites.
    std::vector<Critter*> activeCritters;
    std::vector<sf::Sprite> critterSprites;
    //Pending critters to be spawned.
    std::vector<Critter*> pendingCritters;
    
    //Keeping track of wave number
    int currentWave;
    int maxWave;

    //For smooth movement, track progress
    std::vector<float> critterMoveProgress;
    std::vector<Position> prevPositions;

    //Helper methods:
    void loadResources();
    //Spawn the next critter if the last one has reached at least halfway along the path.
    void trySpawnNextCritter();

};

#endif
