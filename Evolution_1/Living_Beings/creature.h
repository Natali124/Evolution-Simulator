#ifndef CREATURE_H
#define CREATURE_H
#include "living_being.h"
#include "Neural_Network/network.hpp"

class Creature : LivingBeing {
public:
    float physical_strength;
    float energy;
    float eye_sight;
    float visibility;
    Network brain;
    void reproduction();
    virtual std::vector<LivingBeing> get_close();
};

#endif // CREATURE_H
