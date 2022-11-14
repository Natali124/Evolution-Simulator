#ifndef FOOD_H
#define FOOD_H

#include "common.hpp"
class Food {
public:
  Food(); // random value, random position
  Food(Coordinate position); // random value, fixed position
  Food(Coordinate position, double food_value);

  // getters
  Coordinate get_position(){return position;}
  double get_food_value(){return food_value;}
  bool get_is_plant(){return is_plant;}

private:
  // how much energy gives when eaten (which range?? 0 to 1 ???)
  double food_value;

  // is it a plant or dead animal?
  bool is_plant;

  Coordinate position;
};


#endif // FOOD_H
