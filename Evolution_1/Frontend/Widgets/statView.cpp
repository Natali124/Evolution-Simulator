#include "Living_Beings/creature.h"
#include "Living_Beings/living_being.h"
#include "Living_Beings/plant.h"
#include "statView.h"

StatView::StatView(LivingBeing* being, QWidget* parent) : QWidget(parent),
                                                          being(being){
    setTitle();
    setAttribute(Qt::WA_DeleteOnClose); // very important - delete the object from memory when the window is closed
    setWindowFlags(Qt::WindowStaysOnTopHint); // so that it stays on top of the simulation and doesn't get lost
//    setWindowModality(Qt::WindowModal);

    connect(being->environment, &Environment::updated, this, &StatView::update);

    auto layout = new QVBoxLayout;

    auto type = new ParameterDisplay("Being type:", being, &LivingBeing::get_type_string, this);
    auto test_thingie = new ParameterDisplay("Environment simulation step:", being->environment, &Environment::get_simulation_step, this, being->environment);
    auto hp = new ParameterDisplay("Health points:", being, &LivingBeing::get_hp, this, being->environment);
    auto size = new ParameterDisplay("Size:", being, &LivingBeing::get_size, this);

    layout->addWidget(type);
    layout->addWidget(test_thingie);
    layout->addWidget(hp);
    layout->addWidget(size);

    switch(being->type){
        case LivingBeing::Type_LB::plant:{
            auto plant = dynamic_cast<Plant*>(being);
            auto reproduction_rate = new ParameterDisplay("Reproduction rate:", plant, &Plant::get_reproduction_rate, this, plant->environment); layout->addWidget(reproduction_rate);
            break;
        }
        case LivingBeing::Type_LB::creature:{
            auto creature = dynamic_cast<Creature*>(being);

            auto energy = new ParameterDisplay("Energy: ", creature, &Creature::get_energy, this, creature->environment); layout->addWidget(energy);
            auto eyesight = new ParameterDisplay("Eyesight: ", creature, &Creature::get_eye_sight, this, creature->environment); layout->addWidget(eyesight);
            if(creature->get_eat_creature()){
                //predator

            } else {
                //prey

            }
            break;
        }
        default:
            break;
    }

    auto nr_updated = new ParameterDisplay("Updated:", this, &StatView::get_updates, this, being->environment); layout->addWidget(nr_updated);

    layout->addStretch();
    setLayout(layout);

    resize(300, 150);
    show();
}

void StatView::setTitle(std::string title){
    if(title != ""){
        setWindowTitle( QString::fromStdString(title) );
        return;
    }


    title = "View statistiscs for ";
    if(being != nullptr)
        title += being->get_type_string();
    setWindowTitle( QString::fromStdString(title) );
}

void StatView::update(){
    updates ++;
}
