#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include "environment.h"
#include "Neural_Network/network.hpp"

class LivingBeing{
public:
  LivingBeing(); // initializes a living being with alive = true;
  bool alive;
  virtual void reproduction();
};

#endif

//Previous definition of the class
// LIVING_BEING_H
//Coordinate position;
/*enum Type_LB{
    none = -1,
    predator = 0,
    prey = 1,
    plant = 2,
};*/
