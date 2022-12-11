#ifndef BARRIER_H
#define BARRIER_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>


class Barrier: public QGraphicsItem
{
public:
    Barrier();
    Barrier(QRectF block);  // constructs  a barrrier with a given block
    Barrier(QPointF, QPointF);

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

class MouseBarrier: public QGraphicsScene
{
public:
    explicit MouseBarrier(QObject *parent = 0);
    ~MouseBarrier();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QPointF topPos;
    QPointF bottomPos;
    Barrier* barrier;
    //Barrier* prevBar;
};

#endif // BARRIER_H
