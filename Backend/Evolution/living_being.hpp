/** Defines Living Being Class
 *  Declares Properties and (virtual) actions
 */

#ifndef LIVING_BEING_HPP
#define LIVING_BEING_HPP
#import "common.hpp"

class LivingBeing {
public:
  Coordinate get_position(){return position;}
  bool get_is_dead(){return isdead;}
  double size;
  double get_food_value() {return food_value;}

private:
  Coordinate position;
  bool isdead;
  double food_value;
};

#endif // LIVING_BEING_HPP
