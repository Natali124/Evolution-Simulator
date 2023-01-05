#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include "barrier.h"

class PaintScene : public QGraphicsScene
{
   public:
       explicit PaintScene(QObject *parent = 0);
       ~PaintScene();

   private:
       QPointF     previousPoint;      // The coordinates of the previous point
       Barrier* previousRect;
       //bool click_in_bounding_rect;



       void mouseMoveEvent(QGraphicsSceneMouseEvent *event){
           QRectF block = QRectF(event->scenePos().x(), event->scenePos().y(), 10, 10);
           Barrier* barrier = new Barrier(block);
           this->addItem(barrier);
       }
};

#endif // PAINTSCENE_H
