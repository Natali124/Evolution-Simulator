#include "mainmenu.h"
#include "environment.h"
#include "mainmenu.h"
#include <QFile>
#include <QPushButton>
#include <QMessageBox>
#include <QBoxLayout>
#include <QtGui>

MainMenu::MainMenu(QWidget *parent) : QMainWindow(parent), display(CreatureDisplay(this)){

    resize(720,440); //720p
    setWindowTitle("Main Menu");
    setBackgroundImage(":/backgrounds/images/forest.jpg");

    display.resize(440, 440);
//    display.move(720-440, 0);



    QRect rcontent = display.contentsRect();
    display._scene.setSceneRect(0, 0, rcontent.width(), rcontent.height());

    auto btn = new QPushButton(this);
    btn->setText("Test");
    connect(btn, &QPushButton::clicked, this, &MainMenu::randomize_scene);

    for (int i=0; i < 10; i++){
        display.addRandomDot();
    }

    auto btn2 = new QPushButton(this);
    auto btn3 = new QPushButton(this);

    auto leftLayout = new QVBoxLayout;
    leftLayout->addWidget(btn);
    leftLayout->addWidget(btn2);
    leftLayout->addWidget(btn3);

    auto central = new QWidget(this);
    setCentralWidget(central);

    auto mainLayout = new QHBoxLayout;
//    mainLayout->addWidget(btn);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(&display, -1, Qt::AlignCenter);

    QSizePolicy p = display.sizePolicy();
    p.setVerticalPolicy(QSizePolicy::Minimum);
    p.setHorizontalPolicy(QSizePolicy::Minimum);
    p.setHeightForWidth( true );
    display.setSizePolicy( p );

    central->setLayout(mainLayout);
}

void MainMenu::setBackgroundImage(QString filePath){
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}
