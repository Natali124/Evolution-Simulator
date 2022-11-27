#include "plant.h"
#include "living_being.h"
#include "creature.h"
#include<cmath>

Plant::Plant() {
    reproduction_rate = 0;
    type = plant;}

Plant::Plant(float reproduction_rate) {
    this-> reproduction_rate = reproduction_rate;
    type = plant; }

void Plant::carbs(Creature c) {
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);

    c.energy += alpha;
    c.physical_strength -= alpha;
};

void Plant::protein(Creature c){
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);

    c.physical_strength += alpha;
    c.energy -= alpha;
};

void Plant::slimming_effect(Creature c){
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);

    c.eye_sight += alpha;
    c.visibility -= alpha;
};

void Plant::allergenic_effect(Creature c){
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);

    c.visibility += alpha;
    c.eye_sight -= alpha;
};

void Plant::allergenic_protein(Creature c) {
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);

    c.physical_strength += 2*alpha;
    c.energy -=alpha;
    c.eye_sight -= alpha;
};

void Plant::allergenic_carbs(Creature c){
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);

    c.energy += 2*alpha;
    c.physical_strength -= alpha;
    c.eye_sight -= alpha;
};

void Plant::slimming_protein(Creature c) {
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);

    c.physical_strength += 2*alpha;
    c.energy -= alpha;
    c.visibility -= alpha;
};

void Plant::slimming_carbs(Creature c) {
    float ps = size;
    float cs = c.size;
    float d = ps - cs;
    float dif = abs(d);
    float alpha = 1 - (1/dif);

    c.energy += 2*alpha;
    c.physical_strength -= alpha;
    c.visibility -= alpha;
};
