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
    this->base_parameters = parameters; //we save "dna"
}


/* No need normally since we have already a function with parameter, normally there is reproduction_rate in trhose parameters
Plant::Plant(float reproduction_rate) {
    this-> reproduction_rate = reproduction_rate;
    type = plant; }
*/


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
        c.set_energy(c.get_energy() + alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
    };

};


void Plant::protein(Creature &c){
    if (type_plant == 1) {
        float alpha = get_alpha(c);

        c.set_physical_strength(c.get_physical_strength() + alpha);
        c.set_energy(c.get_energy() - alpha);
    };

};

void Plant::slimming_effect(Creature &c){
    if (type_plant == 2) {
    float alpha = get_alpha(c);

    c.set_eye_sight(c.get_eye_sight() + alpha);
    c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::allergenic_effect(Creature &c){
    if (type_plant == 3) {
    float alpha = get_alpha(c);

    c.set_visibility(c.get_visibility() + alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);

    };

};

void Plant::allergenic_protein(Creature &c) {
    if (type_plant == 4) {
    float alpha = get_alpha(c);

    c.set_physical_strength(c.get_physical_strength() + 2*alpha);
    c.set_energy(c.get_energy() - alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);
    };

};

void Plant::allergenic_carbs(Creature &c){
    if (type_plant == 5) {
    float alpha = get_alpha(c);

    c.set_energy(c.get_energy() + 2*alpha);
    c.set_physical_strength(c.get_physical_strength() - alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);
    };

};

void Plant::slimming_protein(Creature &c) {
    if (type_plant == 6) {
    float alpha = get_alpha(c);

    c.set_physical_strength(c.get_physical_strength() + 2*alpha);
    c.set_energy(c.get_energy() - alpha);
    c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::slimming_carbs(Creature &c) {
    if (type_plant == 7) {
        float alpha = get_alpha(c);

        c.set_energy(c.get_energy() + 2*alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
        c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::reproduction(){};
