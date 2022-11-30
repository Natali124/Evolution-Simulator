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

//input_vector : (sleep, eat, attack, move, sleeptime, eatspeed, move_rotate, move_distance)
void Creature::decision(vector<float>input_vector){
    float action = *max_element(input_vector.begin(), input_vector.begin()+4);
    int j = 0;
    for (vector<float>::iterator i=input_vector.begin(); i!=input_vector.begin()+4; i++){
        if (action==*i){
        break;
        }
    j++;
    }
    if(j==0){
        //sleep(sleeptime);
    }
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
