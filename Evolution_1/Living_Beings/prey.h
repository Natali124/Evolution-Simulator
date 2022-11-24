#ifndef PREY_H
#define PREY_H
#include "creature.h"

class Prey : public Creature{
public:
    Prey();
    LivingBeing::Type_LB type;
};

#endif // PREY_H
