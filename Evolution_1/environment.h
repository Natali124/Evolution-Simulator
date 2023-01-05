#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "qgraphicsscene.h"
#include <iostream>
#include <QGraphicsView>

class Environment : public QGraphicsScene
{
    public:
        Environment(); // Creates a 30x30 grid
        Environment(float width, float height); // creates a widthxheight grid

        qreal get_simulation_step();
        qreal get_min_step();
        qreal get_max_step();
        void  set_simulation_step(qreal);
        void mousePressEvent(QGraphicsSceneMouseEvent* event){
            QTransform id;
            QGraphicsItem* touched = itemAt(event->scenePos().x(), event->scenePos().y(), id);
            if (touched != nullptr){
                this->removeItem(touched);
            }
        }
    private:
        qreal simulation_step = 7;
        qreal min_step = 0.3, max_step = 10;
};

#endif // ENVIRONMENT_H
