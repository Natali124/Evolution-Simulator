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

    double t= QRandomGenerator::global()->generateDouble();
    if(t<0.4){
        Creature* aux = new Creature(environment);
        aux->set_Max_energy( QRandomGenerator::global()->bounded(256) );
        aux->parameters[Creature::eat_creature] = 0;
        aux->parameters[Creature::eat_plants] = 1;
        aux->i_eat_creatures = 0;
        aux->i_eat_plants = 1;
        being = aux;
    } else if(t<0.6){
        Creature* aux = new Creature(environment);
        aux->parameters[Creature::eat_creature] = 1;
        aux->parameters[Creature::eat_plants] = 0;
        aux->i_eat_creatures = 1;
        aux->i_eat_plants = 0;
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
