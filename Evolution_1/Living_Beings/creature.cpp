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
    this->base_parameters = parameters; //we save "dna"
    this->brain = brain;

}

void Creature::reproduction() {};
std::vector<LivingBeing> Creature::get_close() {};


void Creature::playstep() {
    if (sleep_time != 0) {
        sleep();
    }
    else if (sleep_time == 0) {
        decision();
    }
};

void Creature::sleep_init(float delta_t) {
    sleep_time = delta_t;
}

void Creature::sleep() {
    float e = get_energy() -1;
    set_energy(e);
    sleep_time-=1;
}




void Creature::set_energy(float e){this->energy = e;}
float Creature::get_energy(){return this->energy;}
void Creature::set_physical_strength(float ps){this->parameters[physical_strength] = ps;}
float Creature::get_physical_strength(){return this->parameters[physical_strength];}
void Creature::set_eye_sight(float es){this->parameters[eye_sight] = es;}
float Creature::get_eye_sight(){return  this->parameters[eye_sight];}
void Creature::set_visibility(float v){this->parameters[visibility] = v;}
float Creature::get_visibility(){return this->parameters[visibility];}
void Creature::set_Max_energy(float me){this->parameters[Max_energy] = me;}
float Creature::get_Max_energy(){return this->parameters[Max_energy];}
bool Creature::get_eat_creature(){return this->parameters[eat_creature];}
bool Creature::get_eat_plants(){return this->parameters[eat_plants];}



/*
Creature::Creature() {physical_strength=0;energy=0;eye_sight=0;visibility=0;brain = Network();}
Creature::Creature(float physical_strength,float energy, float eye_sight, float visibility, Network brain) {
this-> physical_strength = physical_strength,
this-> energy=energy,this->eye_sight= eye_sight,this-> visibility=visibility,this-> brain=brain; };
*/

