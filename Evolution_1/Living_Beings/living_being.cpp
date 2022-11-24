#include "environment.h"
#include "living_being.h"

LivingBeing::LivingBeing(Coordinate position, float size) {
    this->size = size;
    this->position = position;
}

LivingBeing::LivingBeing(){
    size = rand()%2; // random size between 0 and 1?
    position = Coordinate();
}
