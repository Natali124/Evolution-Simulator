#ifndef PREDATOR_H
#define PREDATOR_H
#include "creature.h"

class Predator : Creature{
public:
    Predator();
    LivingBeing::Type_LB type;
};

#endif // PREDATOR_H
