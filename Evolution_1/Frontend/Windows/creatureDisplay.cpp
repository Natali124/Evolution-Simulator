#include "Frontend/mouse.h"
#include "Frontend/Windows/creatureDisplay.h"
#include "Living_Beings/living_being.h"

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
    LivingBeing *being = new LivingBeing;
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
