#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "qgraphicsscene.h"

class Environment : public QGraphicsScene
{
    public:
        Environment(); // Creates a 30x30 grid
        Environment(float width, float height); // creates a widthxheight grid

        qreal get_simulation_step();
        qreal get_min_step();
        qreal get_max_step();
        void  set_simulation_step(qreal);
    private:
        qreal simulation_step = 7;
        qreal min_step = 0.3, max_step = 10;
};

#endif // ENVIRONMENT_H
