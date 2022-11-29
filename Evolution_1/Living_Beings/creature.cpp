#include <random>
#include "creature.h"
#include "Living_Beings/living_being.h"
#include "Neural_Network/network.hpp"

Creature::Creature() {
    std::map<Enum_parameters, float> parameters;
    // in the iteration param refers to an int into Enum_parameters (which does not include the value last)
    for (Enum_parameters param = (Enum_parameters)0 ; param != last; param=(Enum_parameters)(param+1)) {
        float val = (float)rand()/(float)(RAND_MAX); // val is the random value that we will assign to val
        parameters.insert(std::pair<Enum_parameters, float>(param, val));
    };
    // the brain is already constructed by the default constructor in the .h file.
}

Creature::Creature(std::map<Enum_parameters, float> parameters, Network brain) {
    this->parameters = parameters;
    this->brain = brain;
}

void Creature::reproduction() {};
std::vector<LivingBeing> Creature::get_close() {};


void Creature::sleep(float &sleep_time) {
    is_sleeping = true;
    while (sleep_time > 0) {
        playstep();
        sleep_time-=1;
    }
    parameters[Creature::energy] += sleep_time;
    is_sleeping = false;
}
