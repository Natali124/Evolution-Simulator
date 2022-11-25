#ifndef PLANT_H
#define PLANT_H
#include "living_being.h"
#include <map>

class Plant : public LivingBeing
{
public:
    // the enum_parameters is the enumeration that lists the parameters
    // (we overwrite if for the different creatures)
    enum Enum_parameters{reproduction_rate, last};
    // the 'last' parameter is  just there in order to make iteration easier, it has no actual purpuse
    // see https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum

    // CONSTRUCTORS
    // the defaul constructor initialises parameters with some random values
    Plant();
    // this constructor take a std::map<Enum_parameters, float> and creates a creature with such parameters.
    Plant(std::map<Enum_parameters, float> parameters);

    // DATA MEMBERS
    std::map<Enum_parameters, float> parameters;

    // MEMBER FUNCTIONS
    void reproduction();
};

#endif // PLANT_H
