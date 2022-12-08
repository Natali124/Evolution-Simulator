#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsItem>

class Barrier: public QGraphicsItem
{
public:
    Barrier();
    Barrier(QRectF block);  // constructs  a barrrier with a given block

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget);

    QRectF block;
    QColor color;

private:
    qreal width;
    qreal height;
};

#endif // BARRIER_H
