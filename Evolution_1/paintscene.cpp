#include "paintscene.h"
#include "barrier.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{

}

PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Barrier* barrier = new Barrier;
    qreal x = event->scenePos().x();
    qreal y = event->scenePos().y();
    barrier->block.setRect(x, y, 10, 10);
    this->addItem(barrier);
    previousPoint = event->scenePos();
}
