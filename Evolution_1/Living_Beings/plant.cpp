#include "plant.h"
#include "living_being.h"
#include "creature.h"
#include<cmath>

Plant::Plant(){
    std::map<Enum_parameters, float> parameters;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        float val = (float)rand()/(float)RAND_MAX;
        parameters.insert(std::pair<Enum_parameters, float>(param, val));
    }
}


Plant::Plant(std::map<Enum_parameters, float> parameters) {
    this->parameters = parameters;
}


Plant::Plant(float reproduction_rate) {
    this-> reproduction_rate = reproduction_rate;
    type = plant; }


float Plant::get_alpha(Creature &c) {
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);
    return alpha;
}
void Plant::carbs(Creature &c) {
    if (type_plant == 0) {
        float alpha = get_alpha(c);
        c.energy += alpha;
        c.physical_strength -= alpha;};
};

void Plant::protein(Creature &c){
    if (type_plant == 1) {
        float alpha = get_alpha(c);
        c.physical_strength += alpha;
        c.energy -= alpha;};
};

void Plant::slimming_effect(Creature &c){
    if (type_plant == 2) {
    float alpha = get_alpha(c);
    c.eye_sight += alpha;
    c.visibility -= alpha;};
};

void Plant::allergenic_effect(Creature &c){
    if (type_plant == 3) {
    float alpha = get_alpha(c);
    c.visibility += alpha;
    c.eye_sight -= alpha;};
};

void Plant::allergenic_protein(Creature &c) {
    if (type_plant == 4) {
    float alpha = get_alpha(c);
    c.physical_strength += 2*alpha;
    c.energy -=alpha;
    c.eye_sight -= alpha;};
};

void Plant::allergenic_carbs(Creature &c){
    if (type_plant == 5) {
    float alpha = get_alpha(c);
    c.energy += 2*alpha;
    c.physical_strength -= alpha;
    c.eye_sight -= alpha;};
};

void Plant::slimming_protein(Creature &c) {
    if (type_plant == 6) {
    float alpha = get_alpha(c);
    c.physical_strength += 2*alpha;
    c.energy -= alpha;
    c.visibility -= alpha;};
};

void Plant::slimming_carbs(Creature &c) {
    if (type_plant == 7) {
        float alpha = get_alpha(c);
        c.energy += 2*alpha;
        c.physical_strength -= alpha;
        c.visibility -= alpha;};
};

void Plant::reproduction(){};
