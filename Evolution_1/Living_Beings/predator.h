#ifndef PREDATOR_H
#define PREDATOR_H
#include "creature.h"

class Predator : Creature{
public:
    Predator(); // sets type = predator (see enum Type_LB in living_being.hpp)
    LivingBeing::Type_LB type;
};

#endif // PREDATOR_H
