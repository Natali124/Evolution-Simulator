#include "environment.h"
#include "living_being.h"

LivingBeing::LivingBeing() {
    alive = true;
}

void LivingBeing::reproduction(){};

void LivingBeing::advance(int step){

    if (!step) { return; };

    //play_step(); //Ruben's group function
}
