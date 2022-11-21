/** Defines Plant Class
 *  Declares Properties and functions (Actions)
 */

#ifndef CREATURE_H
#define CREATURE_H


#include <iostream>
#include "common.hpp"
#include "living_being.hpp"
#include "food.hpp"

class Creature : LivingBeing {
public:
  Creature(); // initiates random creature at random position
  Creature(Coordinate position); // initiates random creature at position
  Creature(double size, double speed, double endurance, double sight, double life_expectancy); // creates creature with specific attributes at random position
  Creature(Coordinate position, double size, double speed, double endurance, double sight, double life_expectancy); // creates creature with specific attributes at position

  // getters: only visible attributes
  double get_size(){return size;};

  // actions
  Coordinate move(Direction direction, double speed); // moves in the direction (up/down/left/right) with speed in coordinate units/time unit
  void eat(LivingBeing food); // eat food (dead animal or plant)
  void fight(Creature other); // fight another creature
  void sleep(); // do nothing for time unit, gain energy
  Creature reproduce(); // asexual reproduction, returns child

  // being affected from environment
  void lose_health(double amount); // lose health amount
  void time_step(); // anything that happens when time passes (1 time unit)
  Food die(); // when creature dies, remove Creature and creates Food object at current position

protected:
  // Physical attributes (fixed during lifetime)
  // double between 0 and 1double strength;
  double size;
  double speed;
  double endurance;
  double sight;
  double life_expectancy; // if age reaches life_expectancy, creature dies

  // Stats (variable during lifetime)
  // double between 0 and 1
  double satiation; // hunger, 0 = starved, 1 = full
  double energy;
  double health;

  int age;
  Coordinate position;
  bool isdead;

};

#endif // CREATURE_H


