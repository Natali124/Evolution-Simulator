#ifndef CREATURE_H
#define CREATURE_H
#include "living_being.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <map>


class Creature : public LivingBeing {
public:

    // positive double, positive double, positive double, [0, 1], Bool, Bool, double,
    enum Enum_parameters{ physical_strength, Max_energy, eye_sight, visibility, eat_creature, eat_plants, max_hp, last};

    // the 'last' parameter is  just there in order to make iteration easier, it has no actual purpuse
    // see https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum

    // CONSTRUCTOR
    // default constructor that creates a creates a creature with random parameters
    // and a default brain
    Creature();
    // non-default constructor that takes a std::map<Enum_parameters, float> and a Network
    Creature(std::map<Enum_parameters, float>, Network);

    // MEMBER FUNCTIONS
    void reproduction();
    // functions to be taken care of by Flavia, Garance, Ruben, Oskar, Pablo's team
    virtual std::vector<LivingBeing> get_close();
    void eat(LivingBeing &l, float speed);
    void sleep(float &sleep_time);
    void move(float rotation, float distance);
    void attack(Creature &c);

    float get_parameter(Enum_parameters p);


    // DATA MEMBERS
    bool is_sleeping;
    Network brain;


    std::map<Enum_parameters, float> parameters;
    std::map<Enum_parameters, float> base_parameters; //Those are the parameters we use for reproduction

    void set_energy(float e);
    float get_energy();
    void set_physical_strength(float ps);
    float get_physical_strength();
    void set_eye_sight(float es);
    float get_eye_sight();
    void set_visibility(float v);
    float get_visibility();
    void set_Max_energy(float me);
    float get_Max_energy();
    bool get_eat_creature();
    bool get_eat_plants();
    void set_Max_hp(float me);
    float get_Max_hp();
    void set_hp(float me);
    float get_hp();


protected:
    float energy;
    float hp;



};

#endif // CREATURE_H
