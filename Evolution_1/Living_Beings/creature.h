#ifndef CREATURE_H
#define CREATURE_H
#include "living_being.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <map>


class Creature : public LivingBeing {
public:
    enum Enum_parameters{ physical_strength, energy, eye_sight, last };
    // the 'last' parameter is  just there in order to make iteration easier, it has no actual purpuse
    // see https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum

    // CONSTRUCTOR
    // default constructor that creates a creates a creatur with ranom parameters
    // and a default brain
    Creature();
    // non-default constructor that takes a std::map<Enum_parameters, float> and a Network
    Creature(std::map<Enum_parameters, float>, Network);

    // MEMBER FUNCTIONS
    void reproduction();
    // function to be taken care of by Flavia, Garance, Ruben, Oskar, Pablo's team
    virtual std::vector<LivingBeing> get_close();

    //we take as input a vector that's given by the neural network, this vector contains floats
    //for given parameters (sleep, eat, attack, move, sleeptime, eatspeed, move_rotate, move_distance)
    // this function takes one decision depending on the biggest parameter between the sleep, eat, attack, move actions
    void decision(vector<float>input_vector);

    // DATA MEMBERS
    Network brain;
    std::map<Enum_parameters, float> parameters;
};

#endif // CREATURE_H
