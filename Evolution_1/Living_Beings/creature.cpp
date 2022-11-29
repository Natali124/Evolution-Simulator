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



void Creature::set_energy(float e){
    this->parameters[energy] = e;
}
float Creature::get_energy(){
    return this->parameters[energy];

}
void Creature::set_physical_strength(float ps){
    this->parameters[physical_strength] = ps;
}
float Creature::get_physical_strength(){
    return this->parameters[physical_strength];
}
void Creature::set_eye_sight(float es){
    this->parameters[eye_sight] = es;
}
float Creature::get_eye_sight(){
    return  this->parameters[eye_sight];
}
void Creature::set_visibility(float v){
    this->parameters[visibility] = v;
}
float Creature::get_visibility(){
    return this->parameters[visibility];
}




/*
Creature::Creature() {physical_strength=0;energy=0;eye_sight=0;visibility=0;brain = Network();}
Creature::Creature(float physical_strength,float energy, float eye_sight, float visibility, Network brain) {
this-> physical_strength = physical_strength,
this-> energy=energy,this->eye_sight= eye_sight,this-> visibility=visibility,this-> brain=brain; };
*/
