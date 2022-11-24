#include "creature.h"

Creature::Creature() {physical_strength=0;energy=0;eye_sight=0;visibility=0;}
Creature::Creature(float physical_strength,float energy, float eye_sight, float visibility, Network brain) {
this-> physical_strength = physical_strength,
this-> energy=energy,this->eye_sight= eye_sight,this-> visibility=visibility,this-> brain=brain; };
