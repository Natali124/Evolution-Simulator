#include "environment.h"
#include "living_being.h"

LivingBeing::LivingBeing(Coordinate position, float size) {
    type = none;
    this->size = size;
    this->position = position;
}

LivingBeing::LivingBeing(){
    type = none;
    size = 0;
    position = Coordinate();
}
