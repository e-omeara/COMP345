#include "CritterObserver.h"
#include <iostream>

void ConsoleCritterObserver::update(const Critter& critter) {
    Position pos = critter.getPosition();
    std::cout << "[Critter Observer] " << critter.getType()
              << " at (" << pos.x << ", " << pos.y << "), "
              << "HP: " << critter.getHP() << ", "
              << "Speed: " << critter.getSpeed() << ", "
              << "Strength: " << critter.getStrength()
              << (critter.isAlive() ? " (Alive)" : " (Dead)")
              << std::endl;
}
