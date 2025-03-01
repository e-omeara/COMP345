#include "SFMLCritterSimulator.h"
#include <iostream>
#include <thread>

//Constructor, create window and load resources.
SFMLCritterSimulator::SFMLCritterSimulator(Map* map, const std::vector<Position>& path)
    : map(map), path(path), window(sf::VideoMode({600,400}), "Critter Simulation") {
    loadResources();
    // Create one of each critter type initially and put them in pending.
    pendingCritters.push_back(new FastCritter(path));
    pendingCritters.push_back(new TankCritter(path));
    pendingCritters.push_back(new BossCritter(path));
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

//Try to spawn the next critter, conditions are: if no active critters exist or the last one reached halfway through the path.
void SFMLCritterSimulator::trySpawnNextCritter() {
    if (pendingCritters.empty())
        return;
    if (activeCritters.empty() || activeCritters.back()->getPositionIndex() >= (path.size() / 2)) {
        Critter* next = pendingCritters.front();
        pendingCritters.erase(pendingCritters.begin());
        activeCritters.push_back(next);
        std::string type = activeCritters.back()->getType();
        sf::Sprite sprite = (type == "Fast Critter") 
     ? sf::Sprite(fastTexture)
     : (type == "Tank Critter") 
        ? sf::Sprite(tankTexture) 
        : sf::Sprite(bossTexture);

        sprite.setScale({0.5f, 0.5f});
        critterSprites.push_back(sprite);
    }
}


//Update critters: move them along the path and update sprite positions.
void SFMLCritterSimulator::updateCritters(float dt) {
    //For each active critter, call move() once per update interval.
    for(size_t i = 0; i < activeCritters.size(); i++){
        activeCritters[i]->move();
        Position pos = activeCritters[i]->getPosition();
        critterSprites[i].setPosition({pos.x * 40.f, pos.y * 40.f});
    }
    //Check spawn condition.
    trySpawnNextCritter();
}

//Draw the map background for visual clarity, then all critters.
void SFMLCritterSimulator::drawSimulation() {
    window.clear(sf::Color::Black);

    //Get mouse position for tooltip detection, when hovering over critters.
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
    //Draw active critters.
    for(size_t i = 0; i < activeCritters.size(); i++){
        window.draw(critterSprites[i]);
        
        //Draw health bar above each critter.
        float maxHP;
        for (size_t i = 0; i < activeCritters.size(); i++) {
            if (activeCritters[i] == nullptr) {
                std::cerr << "Warning: activeCritters[" << i << "] is null.\n";
                continue;
            }
            maxHP = (activeCritters[i]->getType() == "Fast Critter") ? 20.f :
                          (activeCritters[i]->getType() == "Tank Critter") ? 50.f : 100.f;
            
        }
        float currentHP = static_cast<float>(activeCritters[i]->getHP());
        float ratio = currentHP / maxHP;
        sf::RectangleShape barBack(sf::Vector2f(40.f, 5.f));
        barBack.setFillColor(sf::Color::Red);
        sf::RectangleShape barFront(sf::Vector2f(40.f * ratio, 5.f));
        barFront.setFillColor(sf::Color::Green);
        sf::Vector2f pos = critterSprites[i].getPosition();
        barBack.setPosition({pos.x, pos.y - 10});
        barFront.setPosition({pos.x, pos.y - 10});
        window.draw(barBack);
        window.draw(barFront);
        
        //Draw tooltip if mouse hovers over critters
        if(critterSprites[i].getGlobalBounds().contains({static_cast<float>(mousePos.x),
                                                         static_cast<float>(mousePos.y)})) {
            std::string tip = activeCritters[i]->getType() +
                "\nHP: " + std::to_string(activeCritters[i]->getHP()) +
                "\nSpeed: " + std::to_string(activeCritters[i]->getSpeed()) +
                "\nStrength: " + std::to_string(activeCritters[i]->getStrength());
            sf::Text tooltip(font);
            tooltip.setString(sf::String(tip));
            tooltip.setFillColor(sf::Color::White);
            tooltip.setOutlineColor(sf::Color::Black);
            tooltip.setOutlineThickness(2.f);
            tooltip.setPosition({pos.x, pos.y - 40});
            window.draw(tooltip);
        }
    }
    window.display();
}

//Main simulation loop
void SFMLCritterSimulator::runSimulation() {
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
        
        
        elapsedTime += simulationClock.restart().asSeconds();
        if(elapsedTime >= simulationInterval){
            updateCritters(elapsedTime);
            elapsedTime = 0.f;
        }
        drawSimulation();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    //Cleanup: delete dynamically allocated critters
    for(auto c : activeCritters)
        delete c;
    for(auto c : pendingCritters)
        delete c;

}