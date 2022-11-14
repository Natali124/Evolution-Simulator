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


private:
  Coordinate position;
  bool isdead;
};

#endif // LIVING_BEING_HPP
