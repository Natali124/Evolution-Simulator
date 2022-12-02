#include "environment.h"
#include "math.h"

Environment::Environment() {
    width = 30.0;
    height = 30.0;
}

Environment::Environment(float height, float width) {
    this->width = width;
    this->height = height;
}

float Environment::get_width() {return width;};
float Environment::get_height() {return height;};

// Definition of Coordinate functions
Coordinate::Coordinate(float x, float y) {this->x = x; this-> y = y;};
Coordinate::Coordinate() {x = 0 , y = 0;};


