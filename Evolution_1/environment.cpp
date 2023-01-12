#include "environment.h"
#include "math.h"
#include <QtGui>

Environment::Environment() : QGraphicsScene(0, 0, 30, 30) { }
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

int Environment::nr_beings(){
    return items().size();
}
