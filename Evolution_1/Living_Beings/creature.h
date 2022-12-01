#ifndef CREATURE_H
#define CREATURE_H
#include "living_being.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <map>


class Creature : public LivingBeing {
public:
    enum Enum_parameters{ physical_strength, energy, eye_sight, visibility, last };
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

    void playstep();//playstep for one unit of time
    void eat(LivingBeing &l, float speed);
    void sleep(float &sleep_time);
    void move(float rotation, float distance);
    void attack(Creature &c);

    float get_parameter(Enum_parameters p);


    // DATA MEMBERS
    bool is_sleeping;
    Network brain;
    std::map<Enum_parameters, float> parameters;



};

#endif // CREATURE_H
