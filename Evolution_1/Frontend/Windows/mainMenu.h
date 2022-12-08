
#ifndef MAINMENU_H
#define MAINMENU_H

#include "creatureDisplay.h"
#include <QMainWindow>

//main window for displaying the game
class MainMenu : public QMainWindow{
    public:
        MainMenu(QWidget *parent = nullptr);
//        ~MainMenu();
        CreatureDisplay* getDisplay(){
            return &display;
        }
        void randomize_scene(){
            display._scene.clear();
            for(int i = 0; i < 10; i ++)
                display.addRandomDot();
        }

    private:
        CreatureDisplay display;
        void setBackgroundImage(QString filePath);
};

#endif // MAINMENU_H





