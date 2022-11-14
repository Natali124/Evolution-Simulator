/** Defines common classes
 *  used in other files
 * */
#include "common.hpp"
#include "math.h"

// Definition of Coordinate functions
// copied from td6.
Coordinate::Coordinate(double x_other, double y_other) : x{x_other}, y{y_other} {
}

Coordinate::Coordinate() : Coordinate(0,0) {
}

Coordinate::Coordinate(const Coordinate &other) {
  num_instances += 1;
  x = other.x;
  y = other.y;
}

Coordinate::~Coordinate() {}


double Coordinate::get_x() const {return x;}
double Coordinate::get_y() const {return y;}

void Coordinate::set_x(const double x) {this->x = x;}
void Coordinate::set_y(const double y) {this->y = y;}

Coordinate Coordinate::operator+(const Coordinate& other){
  return Coordinate(x + other.x, y + other.y);
}

Coordinate Coordinate::operator-() {
  return Coordinate(-x, -y);
}

Coordinate Coordinate::operator-(const Coordinate& other) {
  return Coordinate(x - other.x, y - other.y);
}

bool Coordinate::operator==(const Coordinate& other) {
  return (x == other.x && y == other.y);
}

bool Coordinate::operator!=(const Coordinate& other) {
  return ! ((*this) == other);
}

bool Coordinate::operator>(const Coordinate& other) {
  return (x > other.x && y > other.y);
}

bool Coordinate::operator<(const Coordinate& other) {
  return (x < other.x && y < other.y);
}

int Coordinate::num_instances = 0;

int Coordinate::get_num_instances() { return num_instances; }

double Coordinate::get_distance(Coordinate other) {
  return hypot(x - other.get_x(), y - other.get_y());
}
