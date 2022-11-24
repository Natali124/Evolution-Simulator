#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include "environment.h"

class LivingBeing{
public:
  LivingBeing(); //random living being with random arguments
  //on fait les meme constructor que pur creature class
  // un pour random living w rand position, un pour tout les arguments etc
  //et dans la class creature the constructor is inherited from living being
  LivingBeing(Coordinate position, float size);
  bool alive;
  float size;
  Coordinate position;
  enum Type_LB{
      None = -1,
      Predator = 0,
      Prey = 1,
      Plant = 2
  };

  virtual void reproduction();
};

#endif // LIVING_BEING_H
