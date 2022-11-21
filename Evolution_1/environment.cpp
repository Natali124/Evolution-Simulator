#include "environment.h"

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
