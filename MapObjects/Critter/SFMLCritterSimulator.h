#ifndef SFMLCRITTERSIMULATOR_H
#define SFMLCRITTERSIMULATOR_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Critter.h"
#include "Map.h"

class SFMLCritterSimulator {

public:

    //Construct with the made map and the path
    SFMLCritterSimulator(Map* map, const std::vector<Position>& path);

    //Run the critter simulation loop
    void runSimulation();

private:

    Map* map;                    
    std::vector<Position> path;   //The path extracted from the map

    sf::RenderWindow window;
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

    //Helper methods:

    void loadResources();
    //Spawn the next critter if the last one has reached at least halfway along the path.
    void trySpawnNextCritter();
    //Update active critters (move them along the path) and update their sprite positions.
    void updateCritters(float dt);
    //Draw the map background (for visual clarity) and all active critters with health bars and tooltips.
    void drawSimulation();
    //Check if the current wave is finished and load the next wave.
    void checkAndLoadNextWave();
};

#endif
