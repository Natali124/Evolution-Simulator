/** Defines Living Being Class
 *  Declares Properties and (virtual) actions
 */

#ifndef LIVING_BEING_HPP
#define LIVING_BEING_HPP
#import "common.hpp"
#include "environment.hpp"

class LivingBeing : Environment {
public:
  LivingBeing(); //random living being with random arguments
  //on fait les meme constructor que pur creature class
  // un pour random living w rand position, un pour tout les arguments etc
  //et dans la class creature the constructor is inherited from living being
  LivingBeing(Coordinate position);
  Coordinate get_position();
  bool get_is_dead();
  double size;
  double get_food_value();

protected:
  Coordinate position;
  bool is_dead;
  double food_value;
};

#endif // LIVING_BEING_HPP
