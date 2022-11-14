#include "environment.h"

Environment::Environment()
{
    width = 30;
    width = 30;
}

Environment::Environment(int width, int height) {
    this->width = width;
    this->height = height;
}

int Environment::get_width() {return width;};
int Environment::get_heigth() {return heigth;};
