/** Defines common classes
 *  used in other files
 * */
#ifndef COMMON_H
#define COMMON_H

#include <iostream>

enum Direction {up = 0, right = 1, down = 2, left = 3};

// class Coordinate copied from td6
class Coordinate {
public:
  Coordinate(double x_other, double y_other);
  Coordinate();
  Coordinate(const Coordinate &other);
  ~Coordinate();

  double get_x() const;
  double get_y() const;
  void set_x(const double x);
  void set_y(const double y);
  double get_distance(Coordinate other);

  Coordinate operator+(const Coordinate& other);
  Coordinate operator-();
  Coordinate operator-(const Coordinate& other);

  bool operator==(const Coordinate& other);
  bool operator!=(const Coordinate& other);
  bool operator>(const Coordinate& other);
  bool operator<(const Coordinate& other);

  static int get_num_instances();

  friend std::ostream& operator<<(std::ostream& os, const Coordinate& c);

private:
  double x;
  double y;
  static int num_instances;
};

#endif // COMMON_H
