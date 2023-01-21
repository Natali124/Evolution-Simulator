#include "startscreen.h"
#include "QtWidgets/qgridlayout.h"
#include "ui_startscreen.h"

#include <mainwindow.h>

startscreen::startscreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startscreen)
{
    ui->setupUi(this);
    show();
    QString back(":/backgrounds/images/nature-outdoor-forest-background_1308-54338.jpg");
    setBackgroundImage(back);

    ui->StartBut->setStyleSheet("background-color: grey; font-weight:bold; color:white");
}

void startscreen::setBackgroundImage(QString filePath){

    //Sets the background image on the window.

    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}



startscreen::~startscreen()
{
    delete ui;
}

void startscreen::resizeEvent(QResizeEvent *evt)
{
    //This functions make sure the background stretches when you resize the mainwindow.

    stretchBackground();
    //fitDisplay();

    QMainWindow::resizeEvent(evt); //call base implementation
}


void startscreen::stretchBackground(){

    //Stretches background when resizing window.

    QString back(":/backgrounds/images/nature-outdoor-forest-background_1308-54338.jpg");
    QPixmap bkgnd(back);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
}

void startscreen::on_StartBut_clicked()
{
    // When we click on the start button, it closes this window (in the signal/slots on startscreen.ui) and opens the mainwindow.

    new MainWindow;

    // Makes the MainWindow size proportional to the startscreen window
//    auto window = new MainWindow;
//    window->resize(this->size());
}
