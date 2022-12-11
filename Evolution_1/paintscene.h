#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>

class PaintScene : public QGraphicsScene
{
   public:
       explicit PaintScene(QObject *parent = 0);
       ~PaintScene();

   private:
       QPointF     previousPoint;      // The coordinates of the previous point

   private:
       void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
       void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
       void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif // PAINTSCENE_H
