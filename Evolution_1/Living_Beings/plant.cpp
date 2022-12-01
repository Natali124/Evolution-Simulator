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
        float a = c.get_energy() +alpha;
        c.set_energy(a);
        float b = c.get_physical_strength() - alpha;
        c.set_physical_strength(b);}
};

void Plant::protein(Creature &c){
    if (type_plant == 1) {
        float alpha = get_alpha(c);
        float a = c.get_energy() -alpha;
        c.set_energy(a);
        float b = c.get_physical_strength() + alpha;
        c.set_physical_strength(b);}
};

void Plant::slimming_effect(Creature &c){
    if (type_plant == 2) {
    float alpha = get_alpha(c);
    float a = c.get_eye_sight() +alpha;
    c.set_eye_sight(a);
    float b = c.get_visibility() - alpha;
    c.set_visibility(b);}
};

void Plant::allergenic_effect(Creature &c){
    if (type_plant == 3) {
    float alpha = get_alpha(c);
    float a = c.get_eye_sight() -alpha;
    c.set_eye_sight(a);
    float b = c.get_visibility() + alpha;
    c.set_visibility(b);}
};

void Plant::allergenic_protein(Creature &c) {
    if (type_plant == 4) {
    float alpha = get_alpha(c);
    float a = c.get_energy() -alpha;
    c.set_energy(a);
    float b = c.get_physical_strength() + 2*alpha;
    c.set_physical_strength(b);
    float d = c.get_eye_sight() - alpha;
    c.set_eye_sight(d);}
};

void Plant::allergenic_carbs(Creature &c){
    if (type_plant == 5) {
    float alpha = get_alpha(c);
    float a = c.get_energy() +2*alpha;
    c.set_energy(a);
    float b = c.get_physical_strength() - alpha;
    c.set_physical_strength(b);
    float d = c.get_eye_sight() - alpha;
    c.set_eye_sight(d);}
};

void Plant::slimming_protein(Creature &c) {
    if (type_plant == 6) {
    float alpha = get_alpha(c);
    float a = c.get_energy() -alpha;
    c.set_energy(a);
    float b = c.get_physical_strength() + 2*alpha;
    c.set_physical_strength(b);
    float d = c.get_visibility() - alpha;
    c.set_visibility(d);}
};

void Plant::slimming_carbs(Creature &c) {
    if (type_plant == 7) {
        float alpha = get_alpha(c);
        float a = c.get_energy() +2*alpha;
        c.set_energy(a);
        float b = c.get_physical_strength() - alpha;
        c.set_physical_strength(b);
        float d = c.get_visibility() - alpha;
        c.set_visibility(d);}
};

void Plant::reproduction(){};
