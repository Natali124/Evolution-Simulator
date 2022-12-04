#include "Frontend/Windows/mainMenu.h"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>
#include <QHBoxLayout>
#include <QSlider>
#include <QProgressBar>
#include <QCheckBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget *mainWindow = new QWidget;
    mainWindow->setWindowTitle("Choose properties of your new Creature");

    QProgressBar *progress = new QProgressBar;
    QSlider *slider = new QSlider(Qt::Horizontal);

    progress->setRange(1,10);
    slider->setRange(1,10);
    progress->setValue(0);

    QObject::connect(slider, SIGNAL(valueChanged(int)), progress, SLOT(setValue(int)));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(progress);
    mainWindow->setLayout(layout);
    mainWindow->show();

    MainMenu menu;

    menu.show();

    return a.exec();
}
