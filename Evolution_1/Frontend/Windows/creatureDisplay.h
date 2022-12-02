#ifndef CREATUREDISPLAY_H
#define CREATUREDISPLAY_H
#include <QGraphicsView>

class CreatureDisplay : public QGraphicsView{
    public:
        CreatureDisplay(QWidget *parent = nullptr);

        void addRandomDot();
        QGraphicsScene _scene;
        int heightForWidth(int w) const {return w;}
    private:
        QWidget* parentWindow;
};

#endif // CREATUREDISPLAY_H
