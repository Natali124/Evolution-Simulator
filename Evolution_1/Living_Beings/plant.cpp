#include "plant.h"
#include "living_being.h"
#include "creature.h"
#include<cmath>





Plant::Plant():LivingBeing(){
    std::map<Enum_parameters, double> parameters;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        double val = (double)rand()/(double)RAND_MAX;
        parameters.insert(std::pair<Enum_parameters, double>(param, val));
    }
    type = plant;
}


Plant::Plant(std::map<Enum_parameters, double> parameters): Plant() {
    this->parameters = parameters;
    this->base_parameters = parameters; //we save "dna"


    this->set_hp(this->get_Max_hp());

    type = plant;
}

Plant::~Plant() {};


/* No need normally since we have already a function with parameter, normally there is reproduction_rate in trhose parameters
Plant::Plant(double reproduction_rate) {
    this-> reproduction_rate = reproduction_rate;
    type = plant; }
*/

void Plant::is_eaten(Creature &c) {
    double alpha = get_alpha(c);
    if (type_plant == 0) { // carbs
        c.set_energy(c.get_energy() + alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);}

    else if (type_plant == 1) { //protein
            c.set_physical_strength(c.get_physical_strength() + alpha);
            c.set_energy(c.get_energy() - alpha);}

    else if (type_plant == 2) { //slimming_effects
        c.set_eye_sight(c.get_eye_sight() + alpha);
        c.set_visibility(c.get_visibility() - alpha);}

    else if (type_plant == 3) { //allergenic_effect
        c.set_visibility(c.get_visibility() + alpha);
        c.set_eye_sight(c.get_eye_sight() - alpha);}

    else if (type_plant == 4) { // allergenic_protein
        c.set_physical_strength(c.get_physical_strength() + 2*alpha);
        c.set_energy(c.get_energy() - alpha);
        c.set_eye_sight(c.get_eye_sight() - alpha);}

    else if (type_plant == 5) { //allergenic_carbs
        c.set_energy(c.get_energy() + 2*alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
        c.set_eye_sight(c.get_eye_sight() - alpha);}

    else if (type_plant == 6) { //slimming_protein
        c.set_physical_strength(c.get_physical_strength() + 2*alpha);
        c.set_energy(c.get_energy() - alpha);
        c.set_visibility(c.get_visibility() - alpha);}

    else if (type_plant == 7) { //slimming_carbs
        c.set_energy(c.get_energy() + 2*alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
        c.set_visibility(c.get_visibility() - alpha);}
}





void Plant::set_reproduction_rate(double rr){this->parameters[reproduction_rate] = rr;}
double Plant::get_reproduction_rate(){return this->parameters[reproduction_rate];}
void Plant::set_size(double s){this->parameters[size] = s;}
double Plant::get_size(){return this->parameters[size];}
void Plant::set_Max_hp(double ms){this->parameters[Max_hp] = ms;}
double Plant::get_Max_hp(){return this->parameters[Max_hp];}
void Plant::set_hp(double ms){this->hp = ms;}
double Plant::get_hp(){return this->hp;}




void Plant::take_dmg(double dmg){
    this->set_hp(this->get_hp() - dmg);
}


double Plant::get_alpha(Creature &c) {
    double ps = get_size();
    double cs = c.get_size();
    double d = ps - cs;
    double dif = abs(d);
    double alpha = 1 - (1/dif);
    return alpha;
}
void Plant::carbs(Creature &c) {
    if (type_plant == 0) {
        double alpha = get_alpha(c);

        c.set_energy(c.get_energy() + alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
    };

};


void Plant::protein(Creature &c){
    if (type_plant == 1) {
        double alpha = get_alpha(c);


        c.set_physical_strength(c.get_physical_strength() + alpha);
        c.set_energy(c.get_energy() - alpha);
    };


};

void Plant::slimming_effect(Creature &c){
    if (type_plant == 2) {
    double alpha = get_alpha(c);


    c.set_eye_sight(c.get_eye_sight() + alpha);
    c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::allergenic_effect(Creature &c){
    if (type_plant == 3) {
    double alpha = get_alpha(c);


    c.set_visibility(c.get_visibility() + alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);

    };

};

void Plant::allergenic_protein(Creature &c) {
    if (type_plant == 4) {
    double alpha = get_alpha(c);

    c.set_physical_strength(c.get_physical_strength() + 2*alpha);
    c.set_energy(c.get_energy() - alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);
    };

};

void Plant::allergenic_carbs(Creature &c){
    if (type_plant == 5) {
    double alpha = get_alpha(c);


    c.set_energy(c.get_energy() + 2*alpha);
    c.set_physical_strength(c.get_physical_strength() - alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);
    };

};

void Plant::slimming_protein(Creature &c) {
    if (type_plant == 6) {
    double alpha = get_alpha(c);


    c.set_physical_strength(c.get_physical_strength() + 2*alpha);
    c.set_energy(c.get_energy() - alpha);
    c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::slimming_carbs(Creature &c) {
    if (type_plant == 7) {
        double alpha = get_alpha(c);


        c.set_energy(c.get_energy() + 2*alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
        c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::playstep() {
    set_size(1.1*get_size());
    set_hp(1.05*get_Max_hp());
    }
LivingBeing* Plant::reproduction(){
    return nullptr;
} //should add reproduction
/*
void Plant::reproduction(){
    std::map<Enum_parameters, double> param_new_plant;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        double val = normal_distrib(parameters[param],0.1);
        param_new_plant.insert(std::pair<Enum_parameters, double>(param, val));
    }
    Plant p = Plant(param_new_plant);
    return &p;
};
*/
