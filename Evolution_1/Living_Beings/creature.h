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
    float speed;
    Network brain;
    void reproduction();
    virtual std::vector<LivingBeing> get_close();

    void digest(LivingBeing food);
    // eat calls digest, reduces the speed of animal, then later increases its energy



    // n >=0 correspond to the number of ray we will use to get the vision.
    // for now, vision is only in front
    std::vector<int> See(int n);
    int See(int n, int i); // auxilary function for See(int)



    float vision; //distance at which the living being can see
};



#endif // CREATURE_H
