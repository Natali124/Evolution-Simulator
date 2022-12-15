#include "environment.h"
#include "math.h"
#include <QTimer>

//CreatureDisplay::CreatureDisplay(QWidget *parent) : QGraphicsView(parent), _scene(){
//    QBrush brush(QPixmap(":/backgrounds/images/cobblestone.jpg"));
//    _scene.setBackgroundBrush(brush);

//    setScene(&_scene);

//    setRenderHint(QPainter::Antialiasing);
//    setCacheMode(QGraphicsView::CacheBackground);
//    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    setDragMode(QGraphicsView::ScrollHandDrag);
//}

//void CreatureDisplay::add_object(LivingBeing* being){
//    _scene.addItem(being);
//}

//void CreatureDisplay::add_object(Barrier* barrier){
//    _scene.addItem(barrier);
//}

//void CreatureDisplay::remove_object(LivingBeing* being){
//    delete being;
//    _scene.removeItem(being);
//}

//void CreatureDisplay::remove_object(Barrier* barrier){
//    delete barrier;
//    _scene.removeItem(barrier);
//}

//void CreatureDisplay::addRandomDot() {
//    int maxX = width();
//    int maxY = height();
//    int x = std::rand() % maxX;
//    int y = std::rand() % maxY;

//    LivingBeing *being = new LivingBeing;
//    being->setPos(x, y);
//    _scene.addItem(being);
//}

Environment::Environment() : QGraphicsScene(0, 0, 30, 30) { }
Environment::Environment(float height, float width) : QGraphicsScene(0, 0, width, height){ }
