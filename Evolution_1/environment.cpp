#include "environment.h"
#include "math.h"

/*Environment::Environment() {
    width = 30.0;
    height = 30.0;
}

Environment::Environment(float height, float width) {
    this->width = width;
    this->height = height;
}

float Environment::get_width() {return width;};
float Environment::get_height() {return height;};

// Definition of Coordinate functions
Coordinate::Coordinate(float x, float y) {this->x = x; this-> y = y;};
Coordinate::Coordinate() {x = 0 , y = 0;};
*/

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
    _scene.removeItem(being);
}

void CreatureDisplay::remove_object(Barrier* barrier){
    _scene.removeItem(barrier);
}

void CreatureDisplay::addRandomDot() {
    int maxX = width();
    int maxY = height();
    int x = std::rand() % maxX;
    int y = std::rand() % maxY;

    LivingBeing *being = new LivingBeing;
    being->setPos(x, y);
    _scene.addItem(being);
}


