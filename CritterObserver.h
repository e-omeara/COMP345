#ifndef CRITTEROBSERVER_H
#define CRITTEROBSERVER_H

#include "Critter.h"

//Base observer interface for Critter
class CritterObserver {
public:
    virtual void update(const Critter& critter) = 0;
    virtual ~CritterObserver() {}
};

//Observer that displays critter's state to the console
class ConsoleCritterObserver : public CritterObserver {
public:
    void update(const Critter& critter) override;
};

#endif
