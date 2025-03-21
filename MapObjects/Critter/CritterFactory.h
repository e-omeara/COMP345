#ifndef CRITTERFACTORY_H
#define CRITTERFACTORY_H

#include <vector>
#include "Critter.h"

class CritterFactory {
public:
    //Creates a wave of critters based on the current wave level and the movement path
    static std::vector<Critter*> createWave(int waveLevel, const std::vector<Position>& path);
};

#endif
