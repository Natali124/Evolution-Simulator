#include "barrier.h"
#include <QPainter>
Barrier::Barrier(){
    block = QRectF(0, 0, 1, 1); //rect with top left corner (0, 0) and (width, height) = (1, 1)
    color = QColor(128, 128, 128); //grey
}

Barrier::Barrier(QRectF block){
    this->block = block;
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
