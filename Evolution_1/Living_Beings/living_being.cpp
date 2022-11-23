#include "environment.h"
#include "living_being.h"

LivingBeing::LivingBeing(Coordinate position) {this->position = position;};

Coordinate LivingBeing::get_position() {return position;};

bool LivingBeing::get_is_dead() {return is_dead;};

double LivingBeing::get_food_value() {return food_value;};
