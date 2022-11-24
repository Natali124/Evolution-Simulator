#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>

class Environment
{
public:
    Environment(); // Creates a 30x30 grid
    Environment(float width, float height); // creates a widthxheight grid
    float get_width();
    float get_height();
private:
    float width, height;
};


class Coordinate {
public:
    Coordinate(); //default(0,0)
    Coordinate(float x,float y);
    float x;
    float y;
};

#endif // ENVIRONMENT_H
