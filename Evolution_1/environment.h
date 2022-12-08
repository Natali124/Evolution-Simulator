#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "qgraphicsscene.h"

class Environment : public QGraphicsScene
{
    public:
        Environment(); // Creates a 30x30 grid
        Environment(float width, float height); // creates a widthxheight grid
};

#endif // ENVIRONMENT_H
