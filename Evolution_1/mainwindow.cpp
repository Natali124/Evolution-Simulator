#include "mainwindow.h"
#include "Frontend/Widgets/simulationView.h"
#include "Frontend/startscreen/propertyslider.h"
#include "ui_mainwindow.h"
#include "Living_Beings/living_being.h"
#include "Living_Beings/creature.h"
#include "Living_Beings/plant.h"

#include <QRandomGenerator>

int num_pred = 0;
int num_prey = 0;
int num_plant = 0;
int active_creature;


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{

    /*This function is a constructor for the MainWindow class, it creates an instance of the MainWindow
     class and sets up the user interface. It sets the background image, sets the palette for various buttons
    and widgets, and sets the style sheet for the buttons and widgets. It also makes certain buttons and widgets
    invisible and connects the 'creature_list' widget with the 'create_proper_sliders' function. */

    setAttribute(Qt::WA_DeleteOnClose); // very important - delete the object from memory when the window is closed
    // only the start button is visible.
    QString back(":/backgrounds/images/nature-outdoor-forest-background_1308-54338.jpg");
    ui->setupUi(this);
    setBackgroundImage(back);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::transparent);

    ui->simBut->setPalette(pal);
    ui->button_rdm->setPalette(pal);
    ui->button_reset->setPalette(pal);
    ui->button_delete_all->setPalette(pal);
    ui->button_delete_creature->setPalette(pal);
    ui->button_plant->setPalette(pal);
    ui->button_pred->setPalette(pal);
    ui->button_prey->setPalette(pal);
    ui->count_pred->setPalette(pal);
    ui->count_plant->setPalette(pal);
    ui->count_pred->setPalette(pal);

    ui->button_plant->setStyleSheet("color: white; background-color: grey");
    ui->button_pred->setStyleSheet("color: white; background-color: grey");
    ui->button_prey->setStyleSheet("color: white; background-color: grey");
    ui->button_delete_all->setStyleSheet("color: white; background-color: grey");
    ui->button_delete_creature->setStyleSheet("color: white; background-color: grey");
    ui->count_plant->setStyleSheet("color: black; background-color: white");
    ui->count_pred->setStyleSheet("color: black; background-color: white");
    ui->count_prey->setStyleSheet("color: black; background-color: white");

    ui->creature_list->setStyleSheet("color: black; background-color: white");

    ui->button_reset->setStyleSheet("color: white; background-color: grey; font-weight:bold");
    ui->button_rdm->setStyleSheet("color: white; background-color: grey; font-weight:bold");
    ui->simBut->setStyleSheet("color: white; background-color: grey; font-weight:bold");

    ui->simBut->setVisible(false);
    ui->button_rdm->setVisible(false);
    ui->button_reset->setVisible(false);

    connect(ui->creature_list, &QListWidget::itemClicked, this, &MainWindow::create_proper_sliders);

    show();

//    connect(ui->creature_list, SIGNAL(itemClicked(QListWidgetItem*)),
//                this, SLOT(on_creature_list_item_clicked(QListWidgetItem*)));

}


MainWindow::~MainWindow()
{
    delete ui;
    delete env;
}


void MainWindow::setBackgroundImage(QString filePath){

    //Sets the background image on the window.
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}


void MainWindow::resizeEvent(QResizeEvent *evt)
{
    //Stretches background when resizing window.

    stretchBackground();
    //fitDisplay();

    QMainWindow::resizeEvent(evt); //call base implementation
}


void MainWindow::stretchBackground(){
    //This functions make sure the background stretches when you resize the mainwindow.

    QString back(":/backgrounds/images/nature-outdoor-forest-background_1308-54338.jpg");
    QPixmap bkgnd(back);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
}


void MainWindow::on_button_pred_clicked()
{

    // Once you have clicked on the "Add omnivorous creature" button, called button_pred for short,
    // there will be added to creature list the number of omnivorous creatures you have chosen to add and that, sorted.
    // Their name'll be "omnivorous creature" + "number of the omnivorous creature created".

    int val = ui->count_pred->value();
//    qDebug() << "Omnivorous creature:" << val;

    if (num_pred+val > 999) {
        val = 999-num_pred;
    }

    for (int i = num_pred; i < num_pred+val; i++) {
        auto creature = new Creature;
        creature->setObjectName("Omnivorous creature " + QString::number(i+1));
        creature->parameters[Creature::eat_creature] = 1;
        auto item = new BeingItem(creature);
        ui->creature_list->addItem(item);
    }

    num_pred += val;
    ui->creature_list->sortItems();

    // The Simulation button appears, called "simbut" for short, as you can now launch the simulation as you've just created one/some creature(s).

    if ((ui->simBut->isVisible() == false) and (ui->creature_list->count() != 0)) {
        ui->simBut->setVisible(true);
    };
}


void MainWindow::on_button_prey_clicked()
{

    // Once you have clicked on the "Add herbivore creature" button, called button_prey for short,
    // there will be added to creature list the number of herbivore creatures you have chosen to add and that, sorted.
    // Their name'll be "herbivore creature" + "number of the herbivore creature created".

    int val = ui->count_prey->value();
//    qDebug() << "Herbivore creature:" << val;

    if (num_prey+val > 999) {
        val = 999-num_prey;
    }

    for (int i = num_prey; i < num_prey+val; i++) {
        auto creature = new Creature;
        creature->setObjectName("Herbivore creature " + QString::number(i+1));
        auto item = new BeingItem(creature);
        ui->creature_list->addItem(item);
    }

    num_prey += val;
    ui->creature_list->sortItems();

    // The Simulation button appears, called "simbut" for short, as you can now launch the simulation as you've just created one/some creature(s).

    if ((ui->simBut->isVisible() == false) and (ui->creature_list->count() != 0))  {
        ui->simBut->setVisible(true);
    };

}


void MainWindow::on_button_plant_clicked()
{

    // Once you have clicked on the "Add plant" button, called button_plant for short,
    // there will be added to creature list the number of plants you have chosen to add and that, sorted.
    // Their name'll be "plant" + "number of the plant created".

    int val = ui->count_plant->value();
//    qDebug() << "Plants:" << val;

    if (num_plant+val > 999) {
        val = 999-num_plant;
    }

    for (int i = num_plant; i < num_plant+val; i++) {
        auto plant = new Plant;
        plant->setObjectName("Plant " + QString::number(i+1));
        auto item = new BeingItem(plant);
        ui->creature_list->addItem(item);
    }

    num_plant += val;
    ui->creature_list->sortItems();

    // The Simulation button appears, called "simbut" for short, as you can now launch the simulation as you've just created one/some creature(s).

    if ((ui->simBut->isVisible() == false) and (ui->creature_list->count() != 0))  {
        ui->simBut->setVisible(true);
    };
}


void MainWindow::on_button_delete_all_clicked()
{

    // Once you have clicked on the "Delete All" button, all creatures (plants, omnivorous or herbivore) will be deleted from creature_list.

    ui->creature_list->clear();
    num_pred = 0;
    num_plant = 0;
    num_prey = 0;

    // Hide the Simulation button, called "simbut" for short, as you can't launch the simulation with no creatures.
    ui->simBut->setVisible(false);
    clearsliders();
    ui->button_rdm->setVisible(false);
    ui->button_reset->setVisible(false);

}


void MainWindow::on_button_delete_creature_clicked()
{
    // Once you have clicked on the "Delete Creature" button, the selected creature in creature_list will be deleted.
    // We purposely didn't change the following creature's number, to have the user keep track of the property selection he/she chose for each creature.
    // Ex: you have in the creature_list "Plant 1", "Plant 2", "Plant 3", and you delete "Plant 2", then you will have "Plant 1" and "Plant 3" left in the list
    // and not "Plant 1" et "Plant 2" (which is "Plant 3" renamed as "Plant 2").

    QListWidgetItem *it = ui->creature_list->takeItem(ui->creature_list->currentRow());
        delete it;
    clearsliders();
    ui->button_rdm->setVisible(false);
    ui->button_reset->setVisible(false);

    // If the user used this button to delete all creatures from his list, then we hide the Simulation button, called "simbut" for short, as you can't launch the simulation with no creatures.

    int count = ui->creature_list->count();
    if (count == 0) {
        ui->simBut->setVisible(false);
    }
}


void MainWindow::create_proper_sliders(QListWidgetItem* item) {
    auto being = dynamic_cast<BeingItem*>(item)->being;
    clearsliders();
    ui->groupBox->setTitle("Change properties for " + being->objectName());
    if (being->type == LivingBeing::Type_LB::creature) {
        auto creature = dynamic_cast<Creature*>(being);
        ui->verticalLayout_2->addWidget(new PropertySlider("Size", creature, &Creature::set_size, creature->get_size(), ui->groupBox));
        ui->verticalLayout_2->addWidget(new PropertySlider("Max Energy", creature, &Creature::set_Max_energy, creature->get_Max_energy(), ui->groupBox));
        ui->verticalLayout_2->addWidget(new PropertySlider("Max HP", creature, &Creature::set_Max_hp, creature->get_Max_hp(), ui->groupBox));
        ui->verticalLayout_2->addWidget(new PropertySlider("Eye Sight", creature, &Creature::set_eye_sight, creature->get_eye_sight(), ui->groupBox));
        ui->verticalLayout_2->addWidget(new PropertySlider("Visibility", creature, &Creature::set_visibility, creature->get_visibility(), ui->groupBox));
        ui->verticalLayout_2->addWidget(new PropertySlider("Physical Strength", creature, &Creature::set_physical_strength, creature->get_physical_strength(), ui->groupBox));
        // ui->verticalLayout_2->addWidget(new PropertySlider("Digest time", creature, &Creature::set_digest_time, creature->get_digest_time(), ui->groupBox));
    }
    if (being->type == LivingBeing::Type_LB::plant) {
        auto plant = dynamic_cast<Plant*>(being);
        ui->verticalLayout_2->addWidget(new PropertySlider("Size", plant, &Plant::set_size, plant->get_size(), ui->groupBox));
        ui->verticalLayout_2->addWidget(new PropertySlider("Max HP", plant, &Plant::set_Max_hp, plant->get_Max_hp(), ui->groupBox));
        ui->verticalLayout_2->addWidget(new PropertySlider("Reproduction Rate", plant, &Plant::set_reproduction_rate, plant->get_reproduction_rate(), ui->groupBox));
    }
    auto list = findChildren<QWidget*>("Property Slider");
    for (auto i = list.begin(); i != list.end(); i++) {
        auto slider = dynamic_cast<PropertySlider*>(*i);
        connect(ui->button_rdm, &QPushButton::clicked, slider, &PropertySlider::randomise);
        connect(ui->button_reset, &QPushButton::clicked, slider, &PropertySlider::reset);
    }
    ui->button_rdm->setVisible(true);
    ui->button_reset->setVisible(true);
}

void MainWindow::on_simBut_clicked()
{
    auto environment = new Environment();

    int n = ui->creature_list->count();
    for(int i = 0; i < n; i++){
        auto beingitem = dynamic_cast<BeingItem*>(ui->creature_list->item(i));
        auto being = beingitem->being;
        being->environment = environment;

        int maxX = environment->width();
        int maxY = environment->height();
        int x = std::rand() % maxX;
        int y = std::rand() % maxY;
        being->setPos(x, y);

        environment->addItem(being);
    }
    new SimulationView(environment);
}

void MainWindow::clearsliders()
{
    auto list = findChildren<PropertySlider*>("Property Slider");
    for (auto i = list.begin(); i != list.end(); i++) {
        (*i)->deleteLater();
    }
    ui->groupBox->setTitle("");
}
