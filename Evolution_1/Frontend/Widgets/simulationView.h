#ifndef MAINMENU_H
#define MAINMENU_H

#include "Frontend/Widgets/simulationViewWidgets.h"
#include <QMainWindow>
#include <QTimer>

//main window for displaying the game
class SimulationView : public QMainWindow{
    public:
        SimulationView(Environment *environment, QWidget *parent = nullptr);

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
