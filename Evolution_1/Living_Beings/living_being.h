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
  LivingBeing(Coordinate position, float size);
  bool alive;
    
    

  QRectF bounding_rect; // the rectangle in which one will draw the shape() of the LB, might need to be a const
  QPainterPath shape; // the shape inside bounding_rect(), might need to be a const
  void set_bounding_rect(qreal x, qreal y, qreal width, qreal height); // bounding_rect will be initialized with top-left corner in x,y
  void set_shape(); // sets the shape of the LB, everything is inside the bounding_rect



  Coordinate position;
  float get_x();
  float get_y();

  enum Type_LB{
      none = -1,
      predator = 0,
      prey = 1,
      plant = 2,
  };
  Type_LB type;


  // n >=0 correspond to the number of ray we will use to get the vision.
  // for now, vision is only in front
  std::vector<int> See(int n);
  int See(int n, int i); // auxilary function for See(int)
  void playstep();

  float size;

  float get_size();
  void set_size(float size);
  float vision; //distance at which the living being can see
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
