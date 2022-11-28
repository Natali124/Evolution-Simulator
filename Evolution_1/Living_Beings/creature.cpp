#include "creature.h"
#include "Living_Beings/living_being.h"
#include "Neural_Network/network.hpp"
#include <QGraphicsItem>

Creature::Creature() {physical_strength=0; energy=0; eye_sight=0; visibility=0; speed = 0; brain = Network();}
Creature::Creature(float physical_strength,float energy, float eye_sight, float visibility, Network brain) {
this-> physical_strength = physical_strength,
this-> energy=energy,this->eye_sight= eye_sight,this-> visibility=visibility,this-> brain=brain; };


std::vector<int> Creature::See(int n){
    std::vector<int> v; //Here we'll get all the output, It will be of size n

    for (int i=0; i<n; i++){
        v.push_back(this->See(n, i));
    }
    return v;
}



int Creature::See(int n, int i){
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


