#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <QGraphicsView>
#include "living_being.h"
#include "barrier.h"
/*class Environment
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
*/
//this is the placeholder class for the environment display

class CreatureDisplay : public QGraphicsView{
    public:
        CreatureDisplay(QWidget *parent = nullptr);

        void add_object(LivingBeing*);
        void add_object(Barrier*);
        void remove_object(LivingBeing*);
        void remove_object(Barrier*);
        QGraphicsScene _scene;
        int heightForWidth(int w) const {return w;}
};


#endif // ENVIRONMENT_H
