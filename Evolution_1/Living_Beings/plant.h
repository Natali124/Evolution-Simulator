#ifndef PLANT_H
#define PLANT_H
#include "living_being.h"

class Plant : public LivingBeing
{
public:
    Plant();
    Plant(float reproduction_rate);
    float reproduction_rate;
    Type_LB type;
    void reproduction();
};

#endif // PLANT_H
