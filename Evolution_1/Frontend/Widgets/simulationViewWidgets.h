#ifndef CREATUREDISPLAY_H
#define CREATUREDISPLAY_H

#include "environment.h"
#include "qgroupbox.h"
#include "qslider.h"
#include "qtoolbutton.h"
#include <QTimer>
#include <QGraphicsView>

//a class to control the passage of time in the environment
class EnvironmentTimer : public QObject
{
    Q_OBJECT
    public:
        EnvironmentTimer(Environment*);
        QTimer *timer;
        void start();
        void stop();
        Environment* environment;

    public slots:
        void Slot();

    private:
        float timeStep = 1000/33;
};

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

class SimulationSpeedSlider : public QGroupBox{
    public:
        SimulationSpeedSlider(EnvironmentTimer* timer, QWidget *parent = nullptr);

    private:
        EnvironmentTimer* timer;
        QToolButton* button;
        QSlider* slider;

        //0 - 100, last value slider had before pausing by pushing button
        int prev_step = 50;
        bool paused_by_button = true;

        void updateInterval(int);
        void handleToggle();
};

#endif // CREATUREDISPLAY_H
