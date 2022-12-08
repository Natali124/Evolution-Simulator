#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsItem>

class Barrier: public QGraphicsItem
{
public:
    Barrier();
    Barrier(QRectF block);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget);

    QRectF block;
    QColor color;
};

#endif // BARRIER_H
