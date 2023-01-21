#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "qgraphicsscene.h"
#include <QGraphicsScene>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsTextItem>

class Environment : public QGraphicsScene
{
    public:
        Environment(); // Creates a 30x30 grid
        Environment(float width, float height); // creates a widthxheight grid

        qreal get_simulation_step();
        qreal get_min_step();
        qreal get_max_step();
        void  set_simulation_step(qreal);

        bool click_in_bounding_rect = false; // ==true if one clicks on a livingbeing, ==false otherwise
        QGraphicsItem* last_touched = nullptr; // last living being that was touched by a mousePressEvent




    private:

        void mousePressEvent(QGraphicsSceneMouseEvent *event){
            QTransform id; // identity transformation
            if (itemAt(event->scenePos().x(), event->scenePos().y(), id) == nullptr){
                click_in_bounding_rect = false; // we dind't click on any being
            }
            else {
                click_in_bounding_rect = true;
                last_touched = itemAt(event->scenePos().x(), event->scenePos().y(), id); // we clicked on a being
            }
        }

        void mouseMoveEvent(QGraphicsSceneMouseEvent *event){
            if (click_in_bounding_rect == false){ // if we didn't click on a being
            }
            else { // otherwise we move the living being that we clicked on

                 QPointF shift = event->scenePos() - event->lastScenePos();
                 last_touched->moveBy(shift.x(), shift.y());
            }
        }


        qreal simulation_step = 7;
        qreal min_step = 0.3, max_step = 10;
};

#endif // ENVIRONMENT_H
