#include "Frontend/resources.h"
#include "creatureDisplay.h"
#include "Frontend/Windows/mainMenu.h"
#include <QFile>
#include <QPushButton>
#include <QMessageBox>
#include <QBoxLayout>
#include <QWidget>
#include <QGroupBox>

MainMenu::MainMenu(QWidget *parent) : QMainWindow(parent), display(CreatureDisplay(this)){
    resize(720,440); //720p
    display.resize(440, 440);
    setWindowTitle("Evolution Simulator");

    QRect rcontent = display.contentsRect();
    display._scene.setSceneRect(0, 0, rcontent.width(), rcontent.height());

    init_layout();
}

void MainMenu::setBackgroundImage(QString filePath){
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}
void MainMenu::init_layout(){
    setMinimumSize(720,440);

    auto leftLayout = new QGroupBox();
    auto btn = new QPushButton(leftLayout);
    btn->setText("Test");
    connect(btn, &QPushButton::clicked, this, &MainMenu::randomize_scene);

    auto btn2 = new QPushButton(leftLayout);
    auto btn3 = new QPushButton(leftLayout);

    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    leftLayout->setSizePolicy(spLeft);

    auto central = new QWidget(this);
    setCentralWidget(central);

    auto rightLayout = new QGroupBox;

    auto mainLayout = new QHBoxLayout;
    mainLayout->addWidget(leftLayout);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(2);
    rightLayout->setSizePolicy(spRight);

    mainLayout->addWidget(rightLayout);
//    mainLayout->addWidget(&display);
    display.setParent(rightLayout);

    QSizePolicy p = display.sizePolicy();
    p.setVerticalPolicy(QSizePolicy::Minimum);
    p.setHorizontalPolicy(QSizePolicy::Minimum);
    p.setHeightForWidth( true );
    p.setHorizontalStretch(2);
    display.setSizePolicy( p );

    central->setLayout(mainLayout);
}

void MainMenu::resizeEvent(QResizeEvent *evt)
{
    QPixmap bkgnd(BACKGROUND_IMAGE_LINK);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette(); //copy current, not create new
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);

    QMainWindow::resizeEvent(evt); //call base implementation
}
