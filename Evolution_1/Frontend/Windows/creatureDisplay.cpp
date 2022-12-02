#include "Frontend/mouse.h"
#include "Frontend/Windows/creatureDisplay.h"
/*
CreatureDisplay::CreatureDisplay(QWidget *parent) : QGraphicsView(parent), _scene(){
    parentWindow = parent;

    QBrush brush(QPixmap(":/backgrounds/images/cobblestone.jpg"));
    _scene.setBackgroundBrush(brush);

    setScene(&_scene);

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void CreatureDisplay::addRandomDot(){
    int maxX = width();
    int maxY = height();
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;

    Mouse *mouse = new Mouse;
    mouse->setPos(x, y);
    _scene.addItem(mouse);
}
*/
