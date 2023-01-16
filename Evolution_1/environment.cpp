#include "environment.h"
#include "math.h"
#include <QtGui>

Environment::Environment() : QGraphicsScene(0, 0, 500, 500) {
    previousRect = nullptr;
    click_in_bounding_rect = false;
    last_touched = nullptr;
}
Environment::Environment(float height, float width) : QGraphicsScene(0, 0, width, height){ }

void Environment::advance(){
    emit updated();

    //call parent implementation as to advance all children qGraphicsItem's of this object
    QGraphicsScene::advance();
}


//getters/setters
qreal Environment::get_simulation_step(){ return simulation_step; }
void  Environment::set_simulation_step(qreal step){
    if(step < min_step) step = min_step;
    if(step > max_step) step = max_step;

    simulation_step = step;
}
qreal Environment::get_min_step(){ return min_step; }
qreal Environment::get_max_step(){ return max_step; }

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
int Environment::nr_beings(){
    return items().size();
}
