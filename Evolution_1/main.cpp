#include "Frontend/Windows/mainMenu.h"
#include <QApplication>
#include <cstdlib>
#include <QGraphicsScene>
#include <iostream>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QProgressBar>
#include <QCheckBox>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

// #include <QLabel>
// QLabel *label = new QLabel("Gametime!");
// label->show();

    QWidget *mainWindow = new QWidget;
    mainWindow->setWindowTitle("Choose properties of your new Creature");

    QProgressBar *progress = new QProgressBar;
    QSpinBox *spinbox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);
    QSlider *slider2 = new QSlider(Qt::Vertical);

    progress->setRange(1,10);
    spinbox->setRange(1,10);
    slider->setRange(1,10);
    slider2->setRange(1,10);
    progress->setValue(0);

    QObject::connect(slider, SIGNAL(valueChanged(int)), progress, SLOT(setValue(int)));
    QObject::connect(slider2, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
    QObject::connect(spinbox, SIGNAL(valueChanged(int)), slider2, SLOT(setValue(int)));

    QPushButton *button = new QPushButton("Random Properties");
    // button->show();

    QObject::connect(button, SIGNAL(clicked()), slider, SLOT(setValue(rand() % 10)));
    QObject::connect(button, SIGNAL(clicked()), slider2, SLOT(setValue(rand() % 10)));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(progress);
    layout->addWidget(slider2);
    layout->addWidget(spinbox);
    layout->addWidget(button);
    mainWindow->setLayout(layout);
    mainWindow->show();

    MainMenu menu;

    menu.show();

    return a.exec();
}
