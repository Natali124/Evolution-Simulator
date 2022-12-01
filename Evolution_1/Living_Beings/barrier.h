#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsItem>

class Barrier: public QGraphicsItem
{
public:
    QRectF block;

    Barrier();
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // BARRIER_H
