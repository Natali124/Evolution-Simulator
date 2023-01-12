#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include "Neural_Network/network.hpp"
#include "environment.h"
#include <iostream>
#include <vector>
#include <random>

extern int number_LBs;
extern int number_LBs_alive;
extern int number_LBs_dead;
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
  virtual LivingBeing* reproduction();

  //This is the function we'll be using when we need to make an object take damages (because it's been attacked)
  virtual void take_dmg(double dmg);
  //common attributes to plants and creatures
  virtual double get_size() const;
  virtual void set_size(double s);
  virtual double get_hp() const;
  virtual void set_hp(double h);
  bool get_alive() const;
  void set_alive(bool b);
  void set_scene(Environment *s);
  int get_alive_time();
  void increase_alive_time();
  Environment* get_scene() const;
  Type_LB get_type() {return type;};

  double normal_distrib(double parameter, double variance){ //takes a value and randomly returns a value like the normal distribution does with a given variance.
      std::random_device rd;
      std::mt19937 gen(rd());
      std::normal_distribution<double> d(parameter, variance);
      return d(gen);
  }
  virtual void advance(int);

  int number_of_steps_since_beginning = 0;
protected:
  int alive_time = 0;
  Environment *scene;
};

#endif
