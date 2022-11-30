#include <random>
#include "creature.h"
#include "Living_Beings/living_being.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <map>


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


float Creature::get_physical_strength() {return parameters[physical_strength];};
float Creature::get_energy() {return parameters[energy];};
float Creature::get_visibility() {return parameters[visibility];};
float Creature::get_eye_sight() {return parameters[eye_sight];};
//for set functions I have to check if I have to create a new map on the heap and delete the previous one(garance)




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
