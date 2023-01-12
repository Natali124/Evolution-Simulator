#include "plant.h"
#include "living_being.h"
#include "creature.h"
#include "qpainter.h"
#include<cmath>



void Plant::reproduction() {}


Plant::Plant(Environment* environment):LivingBeing(environment){
    std::map<Enum_parameters, float> parameters;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        float val = (float)rand()/(float)RAND_MAX;
//        parameters[param] = val;
        parameters.insert(std::pair<Enum_parameters, float>(param, val));
    }
    type = plant;
}


Plant::Plant(std::map<Enum_parameters, float> parameters): Plant() {
    this->parameters = parameters;
    this->base_parameters = parameters; //we save "dna"


    this->set_hp(this->get_Max_hp());

    type = plant;
}

Plant::~Plant(){}


/* No need normally since we have already a function with parameter, normally there is reproduction_rate in trhose parameters
Plant::Plant(float reproduction_rate) {
    this-> reproduction_rate = reproduction_rate;
    type = plant; }
*/

void Plant::is_eaten(Creature &c) {
    float alpha = get_alpha(c);
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


void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::white);
    painter->drawEllipse(QRectF(-25,-25,25,25));
    painter->drawEllipse(QRectF(0,0,25,25));
    painter->drawEllipse(QRectF(-25,0,25,25));
    painter->drawEllipse(QRectF(0,-25,25,25));
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(QRectF(-15,-15,30,30));

    //call parent implementation of paint
    LivingBeing::paint(painter, option, widget);
}

void Plant::set_reproduction_rate(float rr){this->parameters[reproduction_rate] = rr;}
float Plant::get_reproduction_rate(){return this->parameters[reproduction_rate];}
void Plant::set_size(float s){this->parameters[size] = s;}
float Plant::get_size(){return this->parameters[size];}
void Plant::set_Max_hp(float ms){this->parameters[Max_hp] = ms;}
float Plant::get_Max_hp(){return this->parameters[Max_hp];}
void Plant::set_hp(float ms){this->hp = ms;}
float Plant::get_hp(){return this->hp;}




void Plant::take_dmg(float dmg){
    this->set_hp(this->get_hp() - dmg);
}


float Plant::get_alpha(Creature &c) {
    float ps = get_size();
    float cs = c.get_size();
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


void Plant::playstep() {
    set_size(1.1*get_size());
    set_hp(1.05*get_Max_hp());
} //should add reproduction
/*
void Plant::reproduction(){
    std::map<Enum_parameters, float> param_new_plant;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        float val = normal_distrib(parameters[param]);
        param_new_plant.insert(std::pair<Enum_parameters, float>(param, val));
    }
    Plant* p = new Plant(param_new_plant);
};
*/
