#include "Frontend/Widgets/statView.h"
#include "Frontend/resources.h"
#include "simulationViewWidgets.h"
#include "Frontend/Widgets/simulationView.h"
#include <QFile>
#include <QPushButton>
#include <QMessageBox>
#include <QBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include "omni_win.h"
#include "herb_win.h"
#include "plant_win.h"

SimulationView::SimulationView(Environment *environment, QWidget *parent) : QMainWindow(parent),
                                                                display(environment, this),
                                                                environment(environment),
                                                                timer(EnvironmentTimer(environment)){

    setWindowTitle("Evolution Simulator");
    init_layout();

    // This order of events is necessary because the initial layout of all the elements will not be
    // calculated properly if the window is not shown in the beggining.
    show();
    resize(720, 440);
    setMinimumSize(720,440);
}

void SimulationView::setBackgroundImage(QString filePath){
    //Sets the background image on the window.

    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}

void SimulationView::init_layout(){

    //left half
    auto left_widget = new QWidget(this);
    auto left_layout = new QVBoxLayout;

    auto leftGroupBox = new QGroupBox("Control Panel", left_widget);
    auto layout = new QVBoxLayout;
    leftGroupBox->setLayout(layout);
    leftGroupBox->setStyleSheet("color: black");

    auto btn = new QPushButton(leftGroupBox);
    btn->setText("Test - Spawn 200 creatures");
    connect(btn, &QPushButton::clicked, this, &SimulationView::randomize_scene);
    btn->setStyleSheet("color: black; background-color: white");
    layout->addWidget(btn);


    auto slider = new SimulationSpeedSlider(&timer, leftGroupBox);
    slider->setStyleSheet("color: black");
    layout->addWidget(slider);


    auto add_omn = new QPushButton(leftGroupBox);
    add_omn->setText("Add Omnivorous Creature");
    connect(add_omn, &QPushButton::clicked, this, &SimulationView::openOmniWindow);
    add_omn->setStyleSheet("color: black; background-color: white");

    auto add_herb = new QPushButton(leftGroupBox);
    add_herb->setText("Add Herbivorous Creature");
    connect(add_herb, &QPushButton::clicked, this, &SimulationView::openHerbWindow);
    add_herb->setStyleSheet("color: black; background-color: white");

    auto add_plant = new QPushButton(leftGroupBox);
    add_plant->setText("Add Plant");
    connect(add_plant, &QPushButton::clicked, this, &SimulationView::openPlantWindow);
    add_plant->setStyleSheet("color: black; background-color: white");

    layout->addWidget(add_omn);
    layout->addWidget(add_herb);
    layout->addWidget(add_plant);

    auto being_counter = new ParameterDisplay("Entity count:", environment, &Environment::nr_beings, this, environment);
    being_counter->setStyleSheet("color: black");


    layout->addStretch();
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    left_widget->setSizePolicy(spLeft);

    left_layout->addWidget(leftGroupBox);
    left_layout->addWidget(being_counter);
    left_widget->setLayout(left_layout);
    //-------------------------------------------------------------

    //right half
    auto rightGroupBox = new QGroupBox("Display");
    rightGroupBox->setStyleSheet("color: black; border:1px solid rgb(0, 255, 0);");
    display.setParent(rightGroupBox);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(2);
    rightGroupBox->setSizePolicy(spRight);
    //-------------------------------------------------------------

    //----------bringing them together-----------------------------
    auto mainLayout = new QHBoxLayout;
//    mainLayout->addWidget(leftGroupBox);
    mainLayout->addWidget(left_widget);
    mainLayout->addWidget(rightGroupBox);
    //-------------------------------------------------------------

    //this is so that a layout works on a MainWindow
    auto central = new QWidget(this);
    setCentralWidget(central);
    central->setLayout(mainLayout);
}


void SimulationView::openOmniWindow() {
    // Create a new window
//    QMainWindow* newWindow = new QMainWindow();

//    newWindow->setGeometry(100, 100, 250, 550);

//    QVBoxLayout* layout = new QVBoxLayout();

//        // Create a QLabel
//    QSlider* slider = new QSlider(newWindow);

//        // Add the label to the layout
//    layout->addWidget(slider);

//        // Set the layout of the new window
//    newWindow->setLayout(layout);
     //newWindow->show();

     omni_win omnwin(environment);
     omnwin.setModal(true);
     omnwin.exec();
     emit environment->updated();
    //omnwin =new omni_win(this);
    //omnwin->show();
    }
void SimulationView::openHerbWindow() {
    // Create a new window
//    QMainWindow* newWindow = new QMainWindow();

//    newWindow->setGeometry(100, 100, 250, 550);

//    QVBoxLayout* layout = new QVBoxLayout();

//        // Create a QLabel
//    QSlider* slider = new QSlider(newWindow);

//        // Add the label to the layout
//    layout->addWidget(slider);

//        // Set the layout of the new window
//    newWindow->setLayout(layout);
     //newWindow->show();

     herb_win herbwin(environment);
     herbwin.setModal(true);
     herbwin.exec();
     emit environment->updated();
    //omnwin =new omni_win(this);
    //omnwin->show();
    }

void SimulationView::openPlantWindow() {
    // Create a new window
//    QMainWindow* newWindow = new QMainWindow();

//    newWindow->setGeometry(100, 100, 250, 550);

//    QVBoxLayout* layout = new QVBoxLayout();

//        // Create a QLabel
//    QSlider* slider = new QSlider(newWindow);

//        // Add the label to the layout
//    layout->addWidget(slider);

//        // Set the layout of the new window
//    newWindow->setLayout(layout);
     //newWindow->show();

//     plant_win omnwin;
//     omnwin.setModal(true);
//     omnwin.exec();
    //omnwin =new omni_win(this);
    //omnwin->show();
    Plant_win plantwin(environment);
    plantwin.setModal(true);
    plantwin.exec();
    emit environment->updated();
    }

void SimulationView::resizeEvent(QResizeEvent *evt)
{
    //Stretches background when resizing window.

    stretchBackground();
    fitDisplay();

    QMainWindow::resizeEvent(evt); //call base implementation
}

void SimulationView::stretchBackground(){
    //This functions make sure the background stretches when you resize the mainwindow.

    QPixmap bkgnd(BACKGROUND_IMAGE_LINK);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
}
void SimulationView::fitDisplay(){
    //make display square, center into the right groupbox
    auto parent = display.parentWidget();
    int sz = std::min(parent->width(), parent->height()) - 50;
    display.resize(sz, sz);
    int padx = ( parent->width() - sz ) / 2;
    int pady = ( parent->height() - sz ) / 2;
    display.move(padx, pady);
}
