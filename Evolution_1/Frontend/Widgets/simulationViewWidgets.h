#ifndef CREATUREDISPLAY_H
#define CREATUREDISPLAY_H

#include "environment.h"
#include <QGraphicsView>

//The physical 'window' that displays the given environment, and everything it contains
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
