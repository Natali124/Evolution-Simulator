#include "Frontend/Widgets/simulationViewWidgets.h"
#include "Living_Beings/living_being.h"
#include "Living_Beings/creature.h"
#include "Living_Beings/plant.h"
#include "Frontend/resources.h"
#include <QRandomGenerator>

CreatureDisplay::CreatureDisplay(Environment* env, QWidget *parent) : QGraphicsView(parent), environment(env){
    parentWindow = parent;

    QBrush brush(QPixmap(DISPLAY_BACKGROUND_LINK));
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

    int t=rand()%3;
    if(t==0){
        Creature* aux = new Creature(environment);
        aux->set_Max_energy( QRandomGenerator::global()->bounded(256) );
        being = aux;
    } else if(t==1){
        Creature* aux = new Creature(environment);
        aux->parameters[Creature::eat_creature] = 1; // I don't see any better way to set a creature to be a predator for now, but this is for debugging anyways, not permanent
        being = aux;
    } else{ //for now this isn't possible
        being = new Plant(environment);
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
