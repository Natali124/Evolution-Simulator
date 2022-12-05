#ifndef CREATUREDISPLAY_H
#define CREATUREDISPLAY_H
#include <QGraphicsView>

class CreatureDisplay : public QGraphicsView{
    public:
        CreatureDisplay(QWidget *parent = nullptr);

        void addRandomDot();
        QGraphicsScene _scene;
        void zoomToFit();

        virtual void resizeEvent(QResizeEvent*);
    private:
        QWidget* parentWindow;
};

#endif // CREATUREDISPLAY_H
