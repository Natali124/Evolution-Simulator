#include "Frontend/resources.h"
#include "simulationViewWidgets.h"
#include "Frontend/Widgets/simulationView.h"
#include "qtimer.h"
#include <QFile>
#include <QPushButton>
#include <QMessageBox>
#include <QBoxLayout>
#include <QWidget>
#include <QGroupBox>

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
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}

void SimulationView::init_layout(){

    //left half
    auto leftGroupBox = new QGroupBox("Control Panel");
    auto layout = new QVBoxLayout;
    leftGroupBox->setLayout(layout);

    auto btn = new QPushButton(leftGroupBox);
    btn->setText("Test - Spawn 10 creatures");
    connect(btn, &QPushButton::clicked, this, &SimulationView::randomize_scene);
    layout->addWidget(btn);

    auto btnStart = new QPushButton(leftGroupBox);
    btnStart->setText("Start animation");
    connect(btnStart, &QPushButton::clicked, &timer, &EnvironmentTimer::start);
    layout->addWidget(btnStart);

    auto btnStop = new QPushButton(leftGroupBox);
    btnStop->setText("Stop animation");
    connect(btnStop, &QPushButton::clicked, &timer, &EnvironmentTimer::stop);
    layout->addWidget(btnStop);

    layout->addStretch();
    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(1);
    leftGroupBox->setSizePolicy(spLeft);
    //-------------------------------------------------------------

    //right half
    auto rightGroupBox = new QGroupBox("Display");
    rightGroupBox->setStyleSheet("border:1px solid rgb(0, 255, 0); ");
    display.setParent(rightGroupBox);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(2);
    rightGroupBox->setSizePolicy(spRight);
    //-------------------------------------------------------------

    auto mainLayout = new QHBoxLayout;
    mainLayout->addWidget(leftGroupBox);
    mainLayout->addWidget(rightGroupBox);

    //this is so that a layout works on a MainWindow
    auto central = new QWidget(this);
    setCentralWidget(central);
    central->setLayout(mainLayout);
}

void SimulationView::resizeEvent(QResizeEvent *evt)
{
    stretchBackground();
    fitDisplay();

    QMainWindow::resizeEvent(evt); //call base implementation
}

void SimulationView::stretchBackground(){
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

EnvironmentTimer::EnvironmentTimer(Environment *environment) : environment(environment)
{
    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));
}

void EnvironmentTimer::MyTimerSlot()
{
    environment->advance();
}
void EnvironmentTimer::start(){
    // milisec - 33fps
    timer->start(1000 / 33);
}
void EnvironmentTimer::stop(){
    timer->stop();
}
