#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include "Living_Beings/living_being.h"
#include "barrier.h"

class PaintScene : public QGraphicsScene
{
   public:
       explicit PaintScene(QObject *parent = 0);
       ~PaintScene();

   private:
       QPointF     previousPoint;      // The coordinates of the previous point
       Barrier* previousRect;
       bool click_in_bounding_rect; // ==true if one clicks on a livingbeing, ==false otherwise
       QGraphicsItem* last_touched; // last living being that was touched by a mousePressEvent

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
           if (click_in_bounding_rect == false){ // if we didn't click on a being we build a barrier
               QRectF block = QRectF(event->scenePos().x(), event->scenePos().y(), 10, 10);
               Barrier* barrier = new Barrier(block);
               this->addItem(barrier);
           }
           else { // otherwise we move the living being that we clicked on
                QPointF shift = event->scenePos() - event->lastScenePos();
                last_touched->moveBy(shift.x(), shift.y());
           }
       }
};

#endif // PAINTSCENE_H
