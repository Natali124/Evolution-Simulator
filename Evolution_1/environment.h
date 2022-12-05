#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <QGraphicsView>
#include "Living_Beings/living_being.h"
#include "barrier.h"

class CreatureDisplay : public QGraphicsView{
    public:
        CreatureDisplay(QWidget *parent = nullptr);

        void add_object(LivingBeing*);
        void add_object(Barrier*);
        void remove_object(LivingBeing*);
        void remove_object(Barrier*);
        void addRandomDot();
        QGraphicsScene _scene;
        int heightForWidth(int w) const {return w;}
};


#endif // ENVIRONMENT_H

