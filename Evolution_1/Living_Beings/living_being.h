#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include <QGraphicsItem>
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <QGraphicsItem>


class LivingBeing: public QGraphicsItem{
public:
  LivingBeing(); // initializes a living being with alive = true;
  bool alive;
  QColor color;

  QRectF boundingRect() const;
  QPainterPath shape() const;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

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
