#ifndef MAINMENU_H
#define MAINMENU_H

#include "Frontend/Windows/creatureDisplay.h"
#include <QMainWindow>

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

    private:
        CreatureDisplay display;
        void setBackgroundImage(QString filePath);
        void init_layout();

        void stretchBackground();
        void fitDisplay();
};

#endif // MAINMENU_H
