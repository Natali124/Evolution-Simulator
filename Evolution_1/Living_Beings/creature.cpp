#include <random>
#include "creature.h"
#include "Living_Beings/living_being.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

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


float Creature::get_parameter(Enum_parameters p) {return parameters[p];};
//for set functions I have to check if I have to create a new map on the heap and delete the previous one(garance)


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

//input_vector : (sleep, eat, attack, move, sleep_time, eat_time, move_rotate, move_distance)
void Creature::decision(vector<float>input_vector){
    float action = *max_element(input_vector.begin(), input_vector.begin()+4);
    int j = 0;
    for (vector<float>::iterator i=input_vector.begin(); i!=input_vector.begin()+4; i++){
        if (action==*i) {break;}
        j++;
        }
    if(j){
        sleep(*(input_vector.begin()+4)); //sleep for sleep_time
    }
    if(j==1){
        LivingBeing& food = find_food();
        eat(food, *(input_vector.begin()+5));
    }

}

LivingBeing& Creature::find_food(){
    // this function is gonna return the closest dead living being (that you can eat), or no living being

    // use ruben's get_close that returns a list of the living beings in front of you
    // for each living, check if dead and if edible
}

void Creature::eat(LivingBeing &l, float eat_time){
    // what do you gain when eating?
    //--> gonna depend from what you can eat, (if you eat only animals or plants, set an alpha = 1, if you eat both, set alpha=0.8)
    //-->from the size of the creature l.size
    //--> and depends from the speed eatime (between 0 and 1 --> the faster you eat, the less you gain)
    // so total gain is alpha*l.size*eattime

}
