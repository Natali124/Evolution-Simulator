#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "qgraphicsscene.h"

class Environment : public QGraphicsScene
{
    Q_OBJECT // for the signal

    public:
        Environment(); // Creates a 30x30 grid
        Environment(float width, float height); // creates a widthxheight grid

        virtual void advance();

        qreal get_simulation_step();
        qreal get_min_step();
        qreal get_max_step();
        void  set_simulation_step(qreal);
    private:
        qreal simulation_step = 7;
        qreal min_step = 0.3, max_step = 10;

    //for updating different widgets monitoring game statistics
    // this is pretty inneficient as this is called at every advancement
    // but seeing as we are connecting the update of only a few stat monitors
    // this shouldn't come as a problem. A more efficient solution (but more
    // complicated to write) would be declaring a signal for the change of any
    // value that has a setter
    signals:
        void updated();
};

#endif // ENVIRONMENT_H
