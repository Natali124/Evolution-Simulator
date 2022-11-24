#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include "environment.h"

class LivingBeing{
public:
  LivingBeing();
  LivingBeing(Coordinate position, float size);
  bool alive;
  float size;
  Coordinate position;
  enum Type_LB{
      none = -1,
      predator = 0,
      prey = 1,
      plant = 2,
  };
  Type_LB type;
  virtual void reproduction();
};

#endif // LIVING_BEING_H
