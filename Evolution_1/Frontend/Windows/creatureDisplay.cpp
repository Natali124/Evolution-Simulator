#include "Frontend/mouse.h"
#include "Frontend/Windows/creatureDisplay.h"

CreatureDisplay::CreatureDisplay(QWidget *parent) : QGraphicsView(parent), _scene(){
    parentWindow = parent;

    QBrush brush(QPixmap(":/backgrounds/images/cobblestone.jpg"));
    _scene.setBackgroundBrush(brush);

    _scene.setSceneRect(0, 0, 500, 500);

    setScene(&_scene);

    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void CreatureDisplay::addRandomDot(){
    int maxX = _scene.width();
    int maxY = _scene.height();
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;

    Mouse *mouse = new Mouse;
    mouse->setPos(maxX, maxY);
    _scene.addItem(mouse);
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
