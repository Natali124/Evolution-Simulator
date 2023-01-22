#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "qgraphicsscene.h"
#include "barrier.h"

class Environment : public QGraphicsScene
{
    Q_OBJECT // for the signal

    public:
        Environment(); // Creates a 30x30 grid
        Environment(double width, double height); // creates a widthxheight grid

        virtual void advance();
//        void clear();

        qreal get_simulation_step();
        qreal get_min_step();
        qreal get_max_step();
        void  set_simulation_step(qreal);
        int nr_beings();
    private:
        qreal simulation_step = 7;
        qreal min_step = 0.3, max_step = 10;
//        QPointF     previousPoint;      // The coordinates of the previous point
//        Barrier* previousRect;
//        bool click_in_bounding_rect; // ==true if one clicks on a livingbeing, ==false otherwise
//        QGraphicsItem* last_touched; // last living being that was touched by a mousePressEvent

//        void mousePressEvent(QGraphicsSceneMouseEvent *event){
//            QTransform id; // identity transformation
//            if (itemAt(event->scenePos().x(), event->scenePos().y(), id) == nullptr){
//                click_in_bounding_rect = false; // we dind't click on any being
//            }
//            else {
//                click_in_bounding_rect = true;
//                last_touched = itemAt(event->scenePos().x(), event->scenePos().y(), id); // we clicked on a being
//            }
//        }

//        void mouseMoveEvent(QGraphicsSceneMouseEvent *event){
//            if (click_in_bounding_rect == false){ // if we didn't click on a being we build a barrier
//                QRectF block = QRectF(event->scenePos().x(), event->scenePos().y(), 10, 10);
//                Barrier* barrier = new Barrier(block);
//                this->addItem(barrier);
//            }
//            else { // otherwise we move the living being that we clicked on
//                 QPointF shift = event->scenePos() - event->lastScenePos();
//                 last_touched->moveBy(shift.x(), shift.y());
//            }
//        }

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
