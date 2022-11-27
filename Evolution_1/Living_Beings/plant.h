#ifndef PLANT_H
#define PLANT_H
#include "living_being.h"
#include "creature.h"

class Plant : public LivingBeing
{
public:
    Plant(); //by default reproduction_rate = 0 and type = plant (see enum Type_LB in living_being.hpp)
    Plant(float reproduction_rate);
    float reproduction_rate;
    Type_LB type;
    void reproduction();

    //functions about a creature eating a plant:impact on physical_strength, energy, visibility and eye_sight.
    //variables are incremented/ decremented by a coefficient alpha which depends on the
    // difference between the size of the plant and the size of the creature. The higher this difference is,
    // the less the plant will have an effect on the creature's body.
    // not in coding language: alpha = 1 - (1/ dif(c_size , plant_size))
    // ++ or -- means + or - 2*alpha

    void carbs(Creature c);   // + energy , - strength (c becomes heavier)
    void protein(Creature c); // + strength, - energy (hard to digest)
    void slimming_effect(Creature c);// + eye_sight, - visibility (c becomes slimmer,easier to move the head)
    void allergenic_effect(Creature c);// + visibility, - eye_sight (c has an allergic reaction: body swells)
    void allergenic_protein(Creature c);// ++ strength , - energy and - visibility
    void allergenic_carbs(Creature c);// ++ energy, - strength and - eye_sight
    void slimming_protein(Creature c);//++ strength , - energy and - visibility
    void slimming_carbs(Creature c);// ++ energy, - strength and - visibility

};

#endif // PLANT_H
