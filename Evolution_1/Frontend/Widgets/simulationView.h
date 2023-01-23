#ifndef MAINMENU_H
#define MAINMENU_H

#include "Frontend/Widgets/simulationViewWidgets.h"
#include <QMainWindow>
#include <QTimer>
#include "omni_win.h"

//main window for displaying the game
class SimulationView : public QMainWindow{
    public:
        SimulationView(Environment *environment, QWidget *parent = nullptr);

        CreatureDisplay* getDisplay(){ return &display; }
        void randomize_scene(){ // placeholder
            display.environment->clear();
            for(int i = 0; i < 200; i ++)
                display.addRandomDot();
                environment->current_nr_beings = 20;
            emit environment->updated();
        }
        virtual void resizeEvent(QResizeEvent*);
        Environment* environment;
        EnvironmentTimer timer;

    private:
        CreatureDisplay display;
        void setBackgroundImage(QString filePath);
        void init_layout();
        void openOmniWindow();
        void openHerbWindow();
        void openPlantWindow();
        void stretchBackground();
        void fitDisplay();
        //omni_win *omnwin;

};

#endif // MAINMENU_H
