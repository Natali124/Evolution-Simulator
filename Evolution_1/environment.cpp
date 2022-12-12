#include "environment.h"
#include "math.h"

CreatureDisplay::CreatureDisplay(QWidget *parent) : QGraphicsView(parent), _scene(){
    QBrush brush(QPixmap(":/backgrounds/images/cobblestone.jpg"));
    _scene.setBackgroundBrush(brush);

    setScene(&_scene);

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void CreatureDisplay::add_object(LivingBeing* being){
    _scene.addItem(being);
}

void CreatureDisplay::add_object(Barrier* barrier){
    _scene.addItem(barrier);
}

void CreatureDisplay::remove_object(LivingBeing* being){
    delete being;
    _scene.removeItem(being);
}

void CreatureDisplay::remove_object(Barrier* barrier){
    delete barrier;
    _scene.removeItem(barrier);
}

void CreatureDisplay::addRandomDot() {
    int maxX = width();
    int maxY = height();
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;
    int i = rand();
    LivingBeing *being;
    if (i<RAND_MAX/2){
        being = new Creature;
    }
    else{
        being = new Plant;
    }
    being->setPos(x, y);
    being->set_scene(&_scene);
    _scene.addItem(being);
}


