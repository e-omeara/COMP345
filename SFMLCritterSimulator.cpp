#include "SFMLCritterSimulator.h"
#include "CritterFactory.h"
#include <iostream>
#include <thread>
#include <vector>

//Constructor, create window and load resources.
SFMLCritterSimulator::SFMLCritterSimulator(Map* map, const std::vector<Position>& path)
    : map(map), path(path), currentWave(1), maxWave(3), coinsRewarded(0), healthLost(0) {
    loadResources();
     // Create the first wave using the CritterFactory
     pendingCritters = CritterFactory::createWave(currentWave, path);
}

//Load textures and font.
void SFMLCritterSimulator::loadResources() {
    if(!fastTexture.loadFromFile("fast.png"))
        std::cerr << "Error loading fast.png\n";
    if(!tankTexture.loadFromFile("tank.png"))
        std::cerr << "Error loading tank.png\n";
    if(!bossTexture.loadFromFile("boss.png"))
        std::cerr << "Error loading boss.png\n";
    if(!font.openFromFile("arial.ttf"))
        std::cerr << "Error loading arial.ttf\n";
}

std::vector<Critter *> SFMLCritterSimulator::getCritters(){
    return activeCritters;
}

//Try to spawn the next critter, conditions are: if no active critters exist or the last one reached halfway through the path.
void SFMLCritterSimulator::trySpawnNextCritter() {
    float topCorner = 100.f;
    float tileSize = 20.f;
    

    if (pendingCritters.empty())
        return;
    if (activeCritters.empty() || activeCritters.back()->getPositionIndex() >= (path.size() / 4)) {
        Critter* next = pendingCritters.front();
        pendingCritters.erase(pendingCritters.begin());
        activeCritters.push_back(next);

        //For smooth critter movement, track progress data
        critterMoveProgress.push_back(0.f);
        prevPositions.push_back(path[0]); //Starting position.

        std::string type = activeCritters.back()->getType();
        sf::Sprite sprite = (type == "Fast Critter") 
     ? sf::Sprite(fastTexture)
     : (type == "Tank Critter") 
        ? sf::Sprite(tankTexture) 
        : sf::Sprite(bossTexture);

        sprite.setScale({0.5f, 0.5f});
        sprite.setPosition({topCorner + path[0].x * tileSize, topCorner + path[0].y * tileSize});
        critterSprites.push_back(sprite);
    }
}


//Update critters: move them along the path and update sprite positions
void SFMLCritterSimulator::updateCritters(float dt) {

    float tileSize = 20.f;
    float topCorner = 100.f;
    float simulationInterval = 0.5f; //Time (in seconds) to move one grid cell
    
    //Iterate backwards so that erasing elements does not skip any
    for (int i = static_cast<int>(activeCritters.size()) - 1; i >= 0; --i) {
        //Increment the move progress.
        critterMoveProgress[i] += dt;
        if (critterMoveProgress[i] >= simulationInterval) {
            //Record the current grid cell before moving
            prevPositions[i] = activeCritters[i]->getPosition();
            //Advance the critter.
            activeCritters[i]->move();
            critterMoveProgress[i] -= simulationInterval;
        }

        //Calculation for smooth movement
        float fraction = critterMoveProgress[i] / simulationInterval;
        Position startPos = prevPositions[i];
        Position endPos = activeCritters[i]->getPosition();
        float interpX = startPos.x + (endPos.x - startPos.x) * fraction;
        float interpY = startPos.y + (endPos.y - startPos.y) * fraction;
        critterSprites[i].setPosition({ topCorner + interpX * tileSize, topCorner + interpY * tileSize });
        
        //Removal conditions
        if(activeCritters[i]->hasReachedEnd()) {
            healthLost += activeCritters[i]->stealCoins();
            std::cout << activeCritters[i]->getType() << " reached the exit! Player lost " 
                      << activeCritters[i]->stealCoins() << " health.\n";
            delete activeCritters[i];
            activeCritters.erase(activeCritters.begin() + i);
            critterSprites.erase(critterSprites.begin() + i);
            critterMoveProgress.erase(critterMoveProgress.begin() + i);
            prevPositions.erase(prevPositions.begin() + i);
        } else if(!activeCritters[i]->isAlive()) {
            coinsRewarded += activeCritters[i]->getReward();
            std::cout << activeCritters[i]->getType() << " killed! Player earned " 
                      << activeCritters[i]->getReward() << " coins.\n";
            delete activeCritters[i];
            activeCritters.erase(activeCritters.begin() + i);
            critterSprites.erase(critterSprites.begin() + i);
            critterMoveProgress.erase(critterMoveProgress.begin() + i);
            prevPositions.erase(prevPositions.begin() + i);
        }
    }
    trySpawnNextCritter();
}

bool SFMLCritterSimulator::isWaveComplete() const {
    return activeCritters.empty() && pendingCritters.empty();
}

void SFMLCritterSimulator::startNextWave() {
    if(currentWave < maxWave) {
        currentWave++;
        pendingCritters = CritterFactory::createWave(currentWave, path);
    }
}

//Draw simulation: background, critters, health bars, tooltips, and current wave info
void SFMLCritterSimulator::drawSimulation(sf::RenderWindow* theWindow) {
    //theWindow->clear(sf::Color::Black);

    //Draw current wave information.
    sf::Text waveText(font);
    waveText.setString("Wave: " + std::to_string(currentWave));
    waveText.setFillColor(sf::Color::Yellow);
    waveText.setPosition({10.f, 10.f});
    theWindow->draw(waveText);

    //Get mouse position for tooltip detection.
    sf::Vector2i mousePos = sf::Mouse::getPosition(*theWindow);

    //Draw active critters.
    for (size_t i = 0; i < activeCritters.size(); i++) {
        theWindow->draw(critterSprites[i]);
        
        // Draw health bar above each critter.
        float maxHP = (activeCritters[i]->getType() == "Fast Critter") ? 20.f :
                      (activeCritters[i]->getType() == "Tank Critter") ? 50.f : 100.f;
        // Adjust maxHP to account for scaling (simplistic linear scaling).
        maxHP += (currentWave - 1) * ((activeCritters[i]->getType() == "Fast Critter") ? 5.f :
                 (activeCritters[i]->getType() == "Tank Critter") ? 10.f : 20.f);
                 
        float currentHP = static_cast<float>(activeCritters[i]->getHP());
        float ratio = currentHP / maxHP;
        sf::RectangleShape barBack(sf::Vector2f(40.f, 5.f));
        barBack.setFillColor(sf::Color::Red);
        sf::RectangleShape barFront(sf::Vector2f(40.f * ratio, 5.f));
        barFront.setFillColor(sf::Color::Green);
        sf::Vector2f pos = critterSprites[i].getPosition();
        barBack.setPosition({ pos.x, pos.y - 10 });
        barFront.setPosition({ pos.x, pos.y - 10 });
        theWindow->draw(barBack);
        theWindow->draw(barFront);
        
        // Draw tooltip if mouse hovers over the critter.
        if (critterSprites[i].getGlobalBounds().contains({ static_cast<float>(mousePos.x),
                                                           static_cast<float>(mousePos.y) })) {
            std::string tip = activeCritters[i]->getType() +
                "\nHP: " + std::to_string(activeCritters[i]->getHP()) +
                "\nSpeed: " + std::to_string(activeCritters[i]->getSpeed()) +
                "\nStrength: " + std::to_string(activeCritters[i]->getStrength());
            sf::Text tooltip(font);
            tooltip.setString(tip);
            tooltip.setFillColor(sf::Color::White);
            tooltip.setOutlineColor(sf::Color::Black);
            tooltip.setOutlineThickness(2.f);
            tooltip.setPosition({ pos.x, pos.y - 40 });
            theWindow->draw(tooltip);
        }
    }
    //theWindow->display();
}

//If wave is complete, load the next wave
void SFMLCritterSimulator::checkAndLoadNextWave(sf::RenderWindow* theWindow) {
    if (isWaveComplete()) {
        if (currentWave < maxWave) {
            std::cout << "Wave " << currentWave << " complete. Ready for next wave.\n";
        } else {
            std::cout << "Maximum wave reached. Simulation over.\n";
        }
    }
}

float SFMLCritterSimulator::checkClock(float elapsedTime, sf::Clock* simulationClock){
    float simulationInterval = 0.5f; //Updates every 0.5 sec
    elapsedTime += simulationClock->restart().asSeconds();
    if(elapsedTime >= simulationInterval){
        updateCritters(elapsedTime);
        elapsedTime = 0.f;
    }
    return elapsedTime;
}

//Main simulation loop
void SFMLCritterSimulator::runSimulation(sf::RenderWindow window) {
    sf::Clock simulationClock;
    float simulationInterval = 0.5f; // update every 0.5 sec
    float elapsedTime = 0.f;
    
    //Opening window for simulation output
    while(window.isOpen()){
      
        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>())
                window.close();
            else if(auto keyEvent = event->getIf<sf::Event::KeyPressed>()){
                if(keyEvent->code == sf::Keyboard::Key::Escape)
                    window.close();
                 
                //Create one fast critter at a time by pressing a   
                else if(keyEvent->code == sf::Keyboard::Key::A) {
                    //Create a new fast critter using the path.
                    FastCritter* newCritter = new FastCritter(path);
                    //Push the new critter into the activeCritters vector.
                    activeCritters.push_back(newCritter);
                    
                    //Create a sprite using the new critter's type.
                    sf::Sprite newSprite = (newCritter->getType() == "Fast Critter")
                        ? sf::Sprite(fastTexture)
                        : ((newCritter->getType() == "Tank Critter")
                            ? sf::Sprite(tankTexture)
                            : sf::Sprite(bossTexture));
                    
                    newSprite.setScale({0.5f, 0.5f});
                    critterSprites.push_back(newSprite);
                }
            }
                //Remove one critter at a time by pressing r
                else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))) {
                        
                        if (!activeCritters.empty()) {
                            delete activeCritters.back();
                            activeCritters.pop_back();
                            critterSprites.pop_back();
                        }
                    }
            }
        
        
        elapsedTime = checkClock(elapsedTime, &simulationClock);
        window.clear();
        drawSimulation(&window);
        checkAndLoadNextWave(&window);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    
    
    //Cleanup: delete dynamically allocated critters
    for(auto c : activeCritters)
        delete c;
    for(auto c : pendingCritters)
        delete c;

}