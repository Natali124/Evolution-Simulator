#ifndef MAINMENU_H
#define MAINMENU_H

#include "paintscene.h"
#include "environment.h"
#include <QWidget>
#include <QMainWindow>

//int being_count = 10;

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

        CreatureDisplay display;

    private:
        void setBackgroundImage(QString filePath);
};

#endif // MAINMENU_H
