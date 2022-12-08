#ifndef MAINMENU_H
#define MAINMENU_H

#include "Frontend/Windows/creatureDisplay.h"
#include <QMainWindow>
#include <QTimer>

//a class to control the passage of time in the environment
class EnvironmentTimer : public QObject
{
    Q_OBJECT
    public:
        EnvironmentTimer(Environment*);
        QTimer *timer;
        void start();
        void stop();

    public slots:
        void MyTimerSlot();

    private:
        Environment* environment;
        float timeStep = 1000/33;
};

//main window for displaying the game
class MainMenu : public QMainWindow{
    public:
        MainMenu(Environment *environment, QWidget *parent = nullptr);

        CreatureDisplay* getDisplay(){ return &display; }
        void randomize_scene(){ // placeholder
            display.environment->clear();
            for(int i = 0; i < 10; i ++)
                display.addRandomDot();
        }
        virtual void resizeEvent(QResizeEvent*);
        Environment* environment;
        EnvironmentTimer timer;

    private:
        CreatureDisplay display;
        void setBackgroundImage(QString filePath);
        void init_layout();

        void stretchBackground();
        void fitDisplay();
};

#endif // MAINMENU_H
