#ifndef CREATUREDISPLAY_H
#define CREATUREDISPLAY_H
#include <QGraphicsView>

//this is the placeholder class for the environment display
class CreatureDisplay : public QGraphicsView{
    public:
        CreatureDisplay(QWidget *parent = nullptr);

        void addRandomDot();
        QGraphicsScene _scene;
        int heightForWidth(int w) const {return w;}
};

#endif // CREATUREDISPLAY_H
