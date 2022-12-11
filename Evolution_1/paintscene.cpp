#include "paintscene.h"
#include "barrier.h"
#include <iostream>

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{

}

PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   previousPoint = event->scenePos();
   if (QGraphicsScene::mouseGrabberItem() == nullptr) {
       std::cout << "null" << std::endl;
   }
   std::cout << "hello" << std::endl;

    /*Barrier* barrier = new Barrier;
    qreal x = event->scenePos().x();
    qreal y = event->scenePos().y();
    barrier->block.setRect(x, y, 10, 10);
    this->addItem(barrier);
    previousPoint = event->scenePos();*/
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    std::cout << "hi" << std::endl;
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    // We draw the line with the previous coordinates
    QPointF bottomPos = event->scenePos();
    Barrier* barrier = new Barrier(previousPoint, bottomPos);
    this->addItem(barrier);
};
