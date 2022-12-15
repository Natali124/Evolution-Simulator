// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "mouse.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>
#include <iostream>

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

//! [0]
Mouse::Mouse() : color(QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256),
                       QRandomGenerator::global()->bounded(256))
{
//    setRotation(QRandomGenerator::global()->bounded(360 * 16));
    type=Type(rand()%3);
}
//! [0]

//! [1]
QRectF Mouse::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}
//! [1]

//! [2]
QPainterPath Mouse::shape() const
{
    QPainterPath path;
    path.addRect(-10, -20, 20, 40);
    return path;
}
//! [2]

//! [3]
void Mouse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(type==prey){
        // Body
        painter->setBrush(color);
        painter->drawEllipse(-10, -20, 20, 40);

        // Eyes
        painter->setBrush(Qt::white);
        painter->drawEllipse(-10, -17, 8, 8);
        painter->drawEllipse(2, -17, 8, 8);

        // Nose
        painter->setBrush(Qt::black);
        painter->drawEllipse(QRectF(-2, -22, 4, 4));

        // Pupils
        painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
        painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

        // Ears
        painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
        painter->drawEllipse(-17, -12, 16, 16);
        painter->drawEllipse(1, -12, 16, 16);

        // Tail
        QPainterPath path(QPointF(0, 20));
        path.cubicTo(-5, 22, -5, 22, 0, 25);
        path.cubicTo(5, 27, 5, 32, 0, 30);
        path.cubicTo(-5, 32, -5, 42, 0, 35);
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(path);
    }
    if(type==plant){
        QPoint p1(-25,-25);
        QPoint p2(0,0);
        painter->setBrush(Qt::white);
        painter->drawEllipse(QRectF(-25,-25,0,0));
        p1.setX(0);
        p1.setY(0);
        p2.setX(25);
        p2.setY(25);
        painter->drawEllipse(QRectF(0,0,25,25));
        p1.setX(-25);
        p1.setY(0);
        p2.setX(0);
        p2.setY(25);
        painter->drawEllipse(QRectF(-25,0,0,25));
        p1.setX(0);
        p1.setY(-25);
        p2.setX(25);
        p2.setY(0);
        painter->drawEllipse(QRectF(0,-25,25,0));
        p1.setX(-15);
        p1.setY(-15);
        p2.setX(15);
        p2.setY(15);
        painter->setBrush(Qt::yellow);
        painter->drawEllipse(QRectF(-15,-15,15,15));
    }
    if(type==predator){
        QPoint p1(-25,-25);
        QPoint p2(25,25);
        painter->setBrush(Qt::gray);
        painter->drawEllipse(QRectF(p1,p2));
        p1.setX(-20);
        p1.setY(-20);
        p2.setX(-5);
        p2.setY(-5);
        painter->setBrush(Qt::black);
        painter->drawEllipse(QRectF(p1,p2));
        p1.setX(5);
        p1.setY(-20);
        p2.setX(20);
        p2.setY(-5);
        painter->drawEllipse(QRectF(p1,p2));
        p1.setX(-10);
        p1.setY(-15);
        p2.setX(-5);
        p2.setY(-8);
        painter->setBrush(Qt::white);
        painter->drawEllipse(QRectF(p1,p2));
        p1.setX(15);
        p1.setY(-15);
        p2.setX(20);
        p2.setY(-8);
        painter->drawEllipse(QRectF(p1,p2));
        p1.setX(-15);
        p1.setY(5);
        p2.setX(15);
        p2.setY(15);
        painter->drawEllipse(QRectF(p1,p2));
    }

    //see bounding rect
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::red);
    painter->drawRect(boundingRect());

    //see center
    painter->setPen(Qt::black);
    painter->drawEllipse(QRectF(-1.5,-1.5,3,3));
    painter->setPen(Qt::red);
    painter->drawEllipse(QRectF(-0.5,-0.5,1,1));
}
//! [3]

//! [4]
void Mouse::advance(int step)
{
    if (!step)
        return;
//! [4]
    // Don't move too far away
//! [5]
    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
    if (lineToCenter.length() > 150) {
        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            // Rotate left
            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            // Rotate right
            angle += (angle < Pi / 2) ? 0.25 : -0.25;
        }
    } else if (::sin(angle) < 0) {
        angle += 0.25;
    } else if (::sin(angle) > 0) {
        angle -= 0.25;
//! [5] //! [6]
    }
//! [6]

    // Try not to crash with any other mice
//! [7]
    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
                           << mapToScene(0, 0)
                           << mapToScene(-30, -50)
                           << mapToScene(30, -50));

    for (const QGraphicsItem *item : dangerMice) {
        if (item == this)
            continue;

        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
            // Rotate right
            angle += 0.5;
        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
            // Rotate left
            angle -= 0.5;
//! [7] //! [8]
        }
//! [8] //! [9]
    }
//! [9]

    // Add some random movement
//! [10]
    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
        if (QRandomGenerator::global()->bounded(1))
            angle += QRandomGenerator::global()->bounded(1 / 500.0);
        else
            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
    }
//! [10]

//! [11]
    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

    qreal dx = ::sin(angle) * 10;
    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
}
//! [11]
