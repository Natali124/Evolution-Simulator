#include "environment.h"
#include "living_being.h"

#include <QGraphicsItem>
#include <cmath>





LivingBeing::LivingBeing(){
    alive = true;
    position = Coordinate();
}



float LivingBeing::get_x(){
    return this->position.x;
}
float LivingBeing::get_y(){
    return this->position.y;
}



void LivingBeing::set_bounding_rect(qreal x, qreal y, qreal width, qreal height) { //top left corner at x,y
    this->bounding_rect = QRectF(x, y, width, height);
}

void LivingBeing::set_shape() {   // for now preys and predators are circles, plants are rectangles
    QPainterPath path;
    if (this->type == 0) { // if the LB is a predator
        this->set_bounding_rect(10, 10, 6, 6); // values just for testing purposes, to be changed
        path.addEllipse(this->bounding_rect);
    }

    if (this->type == 1) { // if the LB is a prey
        this->set_bounding_rect(10, 10, 3, 3); // values just for testing purposes, to be changed
        path.addEllipse(this->bounding_rect);
    }

    else if (this->type == 2) { // if the LB is a plant
        this->set_bounding_rect(10, 10, 2, 2); //values just for testing purposes, to be changed
        path.addRect(this->bounding_rect);
    }

    this->shape = path;
}




    //lenght is vision
    QGraphicsLineItem*  Ray = new QGraphicsLineItem(this->get_x(), this->get_y(), this->get_x() + this->vision * cos(teta), this->get_y() + this->vision * cos(teta));
    QList<QGraphicsItem*> list = Ray->collidingItems();

    foreach(QGraphicsItem* i , list)
    {
        int* R = new int(pow(pow(i->x(), 2) + pow(i->y(), 2), 0.5));
        if (*R <r){
            r = *R;
        }
        delete R;
    }
    delete Ray;

    return 1-r;
}
void LivingBeing::reproduction(){};
