#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include <QGraphicsItem>
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <QGraphicsItem>
#include <random>


class LivingBeing : public QGraphicsItem {
public:
  LivingBeing(); // initializes a living being with alive = true
  ~LivingBeing();
  bool alive;
  QColor color;

  QRectF boundingRect() const;
  QPainterPath shape() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
  enum Type_LB{
      none, plant, creature,
  };
  Type_LB type;

  //common attributes to plants and creatures
  virtual void playstep();
  virtual void is_eaten(LivingBeing &c);

  //This is the function we'll be using when we need to make an object take damages (because it's been attacked)
  virtual void take_dmg(float dmg);
  //common attributes to plants and creatures
  virtual float get_size();
  virtual void set_size(float s);
  virtual float get_hp();
  virtual void set_hp(float h);
  bool get_alive();
  void set_alive(bool b);
    
  float normal_distrib(float parameter, float variance){
      std::random_device rd;
      std::mt19937 gen(rd());
      std::normal_distribution<float> d(parameter, variance);
      return d(gen);
  }
  virtual void reproduction();
  virtual void advance(int);
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
