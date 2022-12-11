#include "barrier.h"
#include <QPainter>

Barrier::Barrier(){
    block = QRectF(0, 0, 50, 50); //rect with top left corner (0, 0) and (width, height) = (1, 1)
    color = QColor(128, 128, 128); //grey
}

Barrier::Barrier(QRectF block){
    this->block = block;
    color = QColor(128, 128, 128); //grey
}

Barrier::Barrier(QPointF topPos, QPointF bottomPos){
    this->block.setTopLeft(topPos);
    this->block.setBottomRight(bottomPos);
    color = QColor(128, 128, 128); //grey
}

QRectF Barrier::boundingRect() const {
    return block;
}

QPainterPath Barrier::shape() const {
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}

void Barrier::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget){
    painter->setBrush(color);
    painter->drawRect(block);
}

MouseBarrier::MouseBarrier(QObject *parent) : QGraphicsScene(parent)
{

}

MouseBarrier::~MouseBarrier()
{

}

void MouseBarrier::mousePressEvent(QGraphicsSceneMouseEvent *event){
    topPos = event->pos();
}

void MouseBarrier::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
}

void MouseBarrier::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    bottomPos = event->pos();
    Barrier* barrier = new Barrier;
    barrier->block.setTopLeft(topPos);
    barrier->block.setBottomRight(bottomPos);
    this->addItem(barrier);
    //this->removeItem(prevBar);
    //if (prevBar != NULL) {delete prevBar;};
}




