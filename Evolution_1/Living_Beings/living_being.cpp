#include "environment.h"
#include "living_being.h"

#include <QGraphicsItem>
#include <cmath>


LivingBeing::LivingBeing(Coordinate position, float size) {
    type = none;
    this->size = size;
    this->position = position;
}

LivingBeing::LivingBeing(){
    type = none;
    size = 0;
    position = Coordinate();
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


std::vector<short> LivingBeing::See(int n, double d){
    std::vector<short> v; //Here we'll get all the output, It will be of size n

    for (int i=0; i<n; i++){
        v.push_back(this->See(n, i, d));
    }
    return v;
}

short LivingBeing::See(int n, int i, double d){
    // return a distance score with 256 meaning really close and 0 meaning nothing seen

    //start: x, y ; size = d/(2**k); teta = ((i+1)*pi)/(n+2), this will allow us to get the vision ray at good positions.
    short r=0;
    for (int k=0; k<8; k++){
        double size = d/(pow(2, k));
        if(need_function /*Something in the ray of size d and width Vision_ray_width, can't implement it now*/){
            //r==0=>nothing has been seen
            if (!r){
                r+=1;
            }
            // We use binary search to get the distance of the first seen object
            r+=pow(2, 8-k-1);
        }
    }
    return r;
}
