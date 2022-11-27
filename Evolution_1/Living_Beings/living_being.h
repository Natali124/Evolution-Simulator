#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include "environment.h"
#include <iostream>
#include <vector>
#include <QGraphicsItem>



//Variable we may change, but should be constant:

const double Vision_ray_width = 0.02;


class LivingBeing : public QGraphicsItem { //
public:
  LivingBeing(); // By default Coordinate(), and type = none,  and size = 0
  LivingBeing(Coordinate position, float size);
  bool alive;
  float size;
  QRectF bounding_rect; // the rectangle in which one will draw the shape() of the LB, might need to be a const
  QPainterPath shape; // the shape inside bounding_rect(), might need to be a const
  void set_bounding_rect(qreal x, qreal y, qreal width, qreal height); // bounding_rect will be initialized with top-left corner in x,y
  void set_shape(); // sets the shape of the LB, everything is inside the bounding_rect


  Coordinate position;
  enum Type_LB{
      none = -1,
      predator = 0,
      prey = 1,
      plant = 2,
  };
  Type_LB type;


  // n >=0 correspond to the number of ray we will use to get the vision.
  // for now, vision is only in front
  std::vector<short> See(int n, double d);
  short See(int n, int i, double d); // auxilary function for See(int)



  virtual void reproduction();
};

#endif // LIVING_BEING_H
