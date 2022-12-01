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
    void sleep_init(float delta_t);//called by decision to decide to sleep for a time delta_t
    void sleep();//sleeps for one step : += energy and -= sleep_time
    void move(float rotation, float distance);
    void attack(Creature &c);


    void decision(); //to be implemented(not sure of the format)

    float get_physical_strength();
    float get_energy();
    float get_eye_sight();
    float get_visibility();
    void set_physical_strength(float ps);
    void set_energy(float e);
    void set_eye_sight(float es);
    void set_visibility(float v);




    // DATA MEMBERS
    Network brain;
    std::map<Enum_parameters, float> parameters;

protected:
    float sleep_time;

};

#endif // CREATURE_H
