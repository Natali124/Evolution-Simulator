#ifndef MAINMENU_H
#define MAINMENU_H

#include "creatureDisplay.h"
#include <QMainWindow>

//main window for displaying the game
class MainMenu : public QMainWindow{
    public:
        MainMenu(QWidget *parent = nullptr);

        CreatureDisplay* getDisplay(){ return &display; }
        void randomize_scene(){ // placeholder
            display._scene.clear();
            for(int i = 0; i < 10; i ++)
                display.addRandomDot();
        }
        virtual void resizeEvent(QResizeEvent*);

    private:
        CreatureDisplay display;
        void setBackgroundImage(QString filePath);
        void init_layout();

        void stretchBackground();
        void fitDisplay();
};

#endif // MAINMENU_H
