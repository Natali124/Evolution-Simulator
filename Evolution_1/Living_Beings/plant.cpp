#include "plant.h"
#include "living_being.h"

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

void Plant::reproduction(){};
