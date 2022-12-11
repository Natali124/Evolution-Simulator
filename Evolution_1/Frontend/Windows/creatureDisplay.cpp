#include "Frontend/mouse.h"
#include "Frontend/Windows/creatureDisplay.h"
#include "Living_Beings/creature.h"
#include "Living_Beings/living_being.h"

#include <Living_Beings/plant.h>

CreatureDisplay::CreatureDisplay(Environment* env, QWidget *parent) : QGraphicsView(parent), environment(env){
    parentWindow = parent;

    QBrush brush(QPixmap(":/backgrounds/images/grass.jpg"));
    environment->setBackgroundBrush(brush);

    environment->setSceneRect(0, 0, 500, 500);

    setScene(environment);

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);

    auto policy = sizePolicy();
    policy.setHeightForWidth(true);
}

void CreatureDisplay::addRandomDot(){
    int maxX = environment->width();
    int maxY = environment->height();
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;

//    Mouse *mouse = new Mouse;

//    randomly initializing living beings
    LivingBeing *being;

    int t=rand()%2;
    if(t==0){
        being = new Creature;
    } else if(t==1){
        being = new Plant;
    } else { //for now this isn't possible
        being = new LivingBeing;
    }

    being->setPos(x, y);
    environment->addItem(being);
}

void CreatureDisplay::zoomToFit()
{
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void CreatureDisplay::resizeEvent(QResizeEvent *evt)
{
    zoomToFit();
    QGraphicsView::resizeEvent(evt); //call base implementation
}
