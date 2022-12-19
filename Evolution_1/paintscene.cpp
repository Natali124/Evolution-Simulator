#include "paintscene.h"
#include "barrier.h"
#include <iostream>

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    previousRect = nullptr;
}

PaintScene::~PaintScene()
{

}


/*
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   previousPoint = event->scenePos();
   previousRect = nullptr;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    QPointF bottomPos = event->scenePos();
    Barrier* barrier = new Barrier(previousPoint, bottomPos);
    this->addItem(barrier);
    if (previousRect != nullptr){
        this->removeItem(previousRect);
    }
    previousRect = barrier;
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QPointF bottomPos = event->scenePos();
    Barrier* barrier = new Barrier(previousPoint, bottomPos);
    this->addItem(barrier);
    this->removeItem(previousRect);
};*/
