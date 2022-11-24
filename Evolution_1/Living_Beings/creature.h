#ifndef CREATURE_H
#define CREATURE_H
#include "living_being.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>

class Creature : public LivingBeing {
public:
    Creature(); // by default everything to 0 and calls Network()
    Creature(float physical_strength,float energy, float eye_sight, float visibility, Network brain);
    float physical_strength;
    float energy;
    float eye_sight;
    float visibility;
    Network brain;
    void reproduction();
    virtual std::vector<LivingBeing> get_close();
};

#endif // CREATURE_H
