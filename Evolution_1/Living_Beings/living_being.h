#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include "environment.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <QGraphicsItem>







class LivingBeing : public QGraphicsItem { //
public:
  LivingBeing(); // initializes a living being with alive = true
  bool alive;
    
    

  QRectF bounding_rect; // the rectangle in which one will draw the shape() of the LB, might need to be a const
  QPainterPath shape; // the shape inside bounding_rect(), might need to be a const
  void set_bounding_rect(qreal x, qreal y, qreal width, qreal height); // bounding_rect will be initialized with top-left corner in x,y
  void set_shape(); // sets the shape of the LB, everything is inside the bounding_rect




  enum Type_LB{
      none, plant, creature,
  };
  Type_LB type;


  //common attributes to plants and creatures
  virtual void is_eaten(LivingBeing &c);
  virtual void reproduction();

  //This is the function we'll be using when we need to make an object take damages (because it's been attacked)
  virtual void take_dmg(float dmg);
  //common attributes to plants and creatures
  virtual float get_size();
  virtual void set_size(float s);
  virtual float get_hp();
  virtual void set_hp(float h);
  bool get_alive();
  void set_alive(bool b);

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
