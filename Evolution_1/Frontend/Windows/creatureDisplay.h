#ifndef CREATUREDISPLAY_H
#define CREATUREDISPLAY_H
#include "environment.h"
#include <QGraphicsView>

//this is the placeholder class for the environment display
class CreatureDisplay : public QGraphicsView{
    public:
        CreatureDisplay(Environment* environment, QWidget *parent = nullptr);

        void addRandomDot();
        Environment* environment;
        void zoomToFit();

        virtual void resizeEvent(QResizeEvent*);
    private:
        QWidget* parentWindow;
};

#endif // CREATUREDISPLAY_H
