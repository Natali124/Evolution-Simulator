#include "environment.h"
#include "living_being.h"

LivingBeing::LivingBeing(Coordinate position, float size) {
    this->size = size;
    this->position = position;
}

LivingBeing::LivingBeing(){
    size = 0;
    position = Coordinate();
}
