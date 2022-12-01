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
        path.addEllipse((this->bounding_rect));
    }

    if (this->type == 1) { // if the LB is a prey
        this->set_bounding_rect(10, 10, 3, 3); // values just for testing purposes, to be changed
        path.addEllipse((this->bounding_rect));
    }

    else if (this->type == 2) { // if the LB is a plant
        this->set_bounding_rect(10, 10, 2, 2); //values just for testing purposes, to be changed
        path.addRect(10, 10, 2, 2);
    }

    this->shape = path;
}


std::vector<int> LivingBeing::See(int n){
    std::vector<int> v; //Here we'll get all the output, It will be of size n

    for (int i=0; i<n; i++){
        v.push_back(this->See(n, i));
    }
    return v;
}

int LivingBeing::See(int n, int i){
    // return a distance score with 0 meaning really close and 256 meaning nothing seen (see only the closest object)

    //start: x, y; teta = ((i+1)*pi)/(n+2), this will allow us to get the vision ray at good positions.
    int r=0;
    double teta = ((i+1)*3.14)/(n+2);


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

float LivingBeing::get_size(){};
void LivingBeing::set_size(float s){};
