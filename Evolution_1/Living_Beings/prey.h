#ifndef PREY_H
#define PREY_H
#include "creature.h"

class Prey : public Creature{
public:
    Prey(); // sets type = prey (see enum Type_LB in living_being.hpp)
    LivingBeing::Type_LB type;
};

#endif // PREY_H
