#include "simulationViewWidgets.h"
#include "qboxlayout.h"
#include "qtoolbutton.h"
#include "qslider.h"
#include "qgroupbox.h"
#include "QDebug"

SimulationSpeedSlider::SimulationSpeedSlider(EnvironmentTimer* timer, QWidget* parent) : QGroupBox(parent),
                                                                                         timer(timer){
    setTitle("Speed Control");
    setAlignment(Qt::AlignHCenter);

    button = new QToolButton(this);
    slider = new QSlider(Qt::Horizontal, this);

    button->setText("⏵");
    slider->setMinimum(0);
    slider->setMaximum(100);
    connect(slider, &QSlider::valueChanged, this, &SimulationSpeedSlider::updateInterval);
    connect(button, &QToolButton::clicked, this, &SimulationSpeedSlider::handleToggle);

    auto layout = new QHBoxLayout();
    layout->addWidget(button);
    layout->addWidget(slider);
    setLayout(layout);
}

//slider value change - can be triggered by button press
void SimulationSpeedSlider::updateInterval(int value){
    if(value == 0){
        timer->stop();
        button->setText("⏵");

        return;
    }
    paused_by_button = false;
    button->setText("⏸");

    qreal minstep = timer->environment->get_min_step();
    qreal maxstep = timer->environment->get_max_step();
    qreal step = minstep + (maxstep - minstep) * (value - 0) / 100;

    timer->environment->set_simulation_step(step);
    timer->start();
}

//button press
void SimulationSpeedSlider::handleToggle(){
    if(slider->value() != 0){
        prev_step = slider->value();
        paused_by_button = true;

        slider->setValue(0);
    } else {
        if(!paused_by_button) slider->setValue(50);
        else slider->setValue(prev_step);
    }
}
