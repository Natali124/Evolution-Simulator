#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>

int num_pred = 0;
int num_prey = 0;
int num_plant = 0;
int active_creature;

bool ListWidget::operator<(const QListWidgetItem &other) const
{

                std::cout << other.text().toStdString() << " " << other.text().toStdString() << std::endl;
                return other.text().toFloat() < other.text().toFloat();


}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    // only the start button is visible.
    QString back(":/backgrounds/images/nature-outdoor-forest-background_1308-54338.jpg");
    ui->setupUi(this);
    setBackgroundImage(back);
    ui->simBut->setVisible(false);

    ListWidget* creature_list2 = new ListWidget();
    ui->groupBox_2->setLayout(new QVBoxLayout);
    ui->groupBox_2->layout()->addWidget(creature_list2);

    ui->button_prey->setVisible(false);
    ui->button_pred->setVisible(false);
    ui->button_plant->setVisible(false);
    ui->button_delete_all->setVisible(false);
    ui->button_delete_creature->setVisible(false);

    ui->count_pred->setVisible(false);
    ui->count_prey->setVisible(false);
    ui->count_plant->setVisible(false);

    ui->line_1->setVisible(false);
    ui->line_2->setVisible(false);
    ui->line_3->setVisible(false);

    ui->groupBox_2->setVisible(false);

    ui->groupBox->setVisible(false);
    ui->groupBox->setStyleSheet("color: white; font-weight:bold; font-size:20pt");
    ui->P_strength_t->setStyleSheet("color: white; font-weight:bold");
    ui->max_energy_t->setStyleSheet("color: white; font-weight:bold");
    ui->max_energy_n->setStyleSheet("color: black; background-color: white");
    ui->eye_sight_t->setStyleSheet("color: white; font-weight:bold");
    ui->eye_sight_n->setStyleSheet("color: black; background-color: white");
    ui->visibility_t->setStyleSheet("color: white; font-weight:bold");
    ui->visibility_n->setStyleSheet("color: black; background-color: white");
    ui->max_health_t->setStyleSheet("color: white; font-weight:bold");
    ui->max_health_n->setStyleSheet("color: black; background-color: white");
    ui->size_t->setStyleSheet("color: white; font-weight:bold");
    ui->size_n->setStyleSheet("color: black; background-color: white");
    ui->button_plant->setStyleSheet("color: white; background-color: grey");
    ui->button_pred->setStyleSheet("color: white; background-color: grey");
    ui->button_prey->setStyleSheet("color: white; background-color: grey");
    ui->button_delete_all->setStyleSheet("color: white; background-color: grey");
    ui->button_delete_creature->setStyleSheet("color: white; background-color: grey");
    creature_list2->setStyleSheet("background-color:white; color: black");
    ui->count_plant->setStyleSheet("color: black; background-color: white");
    ui->count_pred->setStyleSheet("color: black; background-color: white");
    ui->count_prey->setStyleSheet("color: black; background-color: white");

    ui->button_reset->setStyleSheet("color: white; background-color: grey; font-weight:bold");
    ui->startBut->setStyleSheet("background-color: grey; font-weight:bold; color:white");
    ui->button_rdm->setStyleSheet("color: white; background-color: grey; font-weight:bold");
    ui->P_strength_n->setStyleSheet("color: black; background-color: white");
    ui->simBut->setStyleSheet("color: white; background-color: grey; font-weight:bold");



    //connect(creature_list2, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_creature_list_item_clicked(QListWidgetItem*)));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setBackgroundImage(QString filePath){
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}


void MainWindow::resizeEvent(QResizeEvent *evt)
{
    stretchBackground();
    //fitDisplay();

    QMainWindow::resizeEvent(evt); //call base implementation
}


void MainWindow::stretchBackground(){
    QString back(":/backgrounds/images/nature-outdoor-forest-background_1308-54338.jpg");
    QPixmap bkgnd(back);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
}


void MainWindow::on_startBut_clicked()
{
    // Once you have clicked on the start button, the original display is now available to click on.
    // Except the simulate button, and the creature's properties' selection, as you haven't created any creature yet.

    ui->startBut->setVisible(false);
    ui->button_prey->setVisible(true);
    ui->button_pred->setVisible(true);
    ui->button_plant->setVisible(true);
    ui->count_pred->setVisible(true);
    ui->count_prey->setVisible(true);
    ui->count_plant->setVisible(true);
    ui->line_1->setVisible(true);
    ui->line_2->setVisible(true);
    ui->line_3->setVisible(true);
    ui->groupBox_2->setVisible(true);
    ui->button_delete_all->setVisible(true);
    ui->button_delete_creature->setVisible(true);
}


void MainWindow::on_button_pred_clicked()
{

    // Once you have clicked on the "Add omnivorous creature" button, called button_pred for short,
    // there will be added to creature list the number of omnivorous creatures you have chosen to add and that, sorted.
    // Their name'll be "omnivorous creature" + "number of the omnivorous creature created".

    int val = ui->count_pred->value();
    qDebug() << "Omnivorous creature:" << val;

    ListWidget* creature_list = ui->groupBox_2->findChild<ListWidget*>();

    for (int i = num_pred; i < num_pred+val; i++) {
        creature_list->addItem("Omnivorous creature " + QString::number(i+1));
    }

    num_pred += val;


    // The Simulation button appears, called "simbut" for short, as you can now launch the simulation as you've just created one/some creature(s).

    if (ui->simBut->isVisible() == false) {
        ui->simBut->setVisible(true);
    };

    QObject::connect(ui->simBut, &QPushButton::clicked, this, &QWidget::close);
}


void MainWindow::on_button_prey_clicked()
{

    // Once you have clicked on the "Add herbivore creature" button, called button_prey for short,
    // there will be added to creature list the number of herbivore creatures you have chosen to add and that, sorted.
    // Their name'll be "herbivore creature" + "number of the herbivore creature created".

    int val = ui->count_prey->value();
    qDebug() << "Herbivore creature:" << val;

    ListWidget* creature_list = ui->groupBox_2->findChild<ListWidget*>();

    for (int i = num_prey; i < num_prey+val; i++) {
        creature_list->addItem("Herbivore creature " + QString::number(i+1));
    }

    num_prey += val;


    // The Simulation button appears, called "simbut" for short, as you can now launch the simulation as you've just created one/some creature(s).

    if (ui->simBut->isVisible() == false) {
        ui->simBut->setVisible(true);
    };
    QObject::connect(ui->simBut, &QPushButton::clicked, this, &QWidget::close);
}


void MainWindow::on_button_plant_clicked()
{

    // Once you have clicked on the "Add plant" button, called button_plant for short,
    // there will be added to creature list the number of plants you have chosen to add and that, sorted.
    // Their name'll be "plant" + "number of the plant created".

    int val = ui->count_plant->value();
    qDebug() << "Plants:" << val;

    ListWidget* creature_list = ui->groupBox_2->findChild<ListWidget*>();

    for (int i = num_plant; i < num_plant+val; i++) {
        creature_list->addItem("Plant " + QString::number(i+1));
    }

    num_plant += val;


    // The Simulation button appears, called "simbut" for short, as you can now launch the simulation as you've just created one/some creature(s).

    if (ui->simBut->isVisible() == false) {
        ui->simBut->setVisible(true);
    };
    QObject::connect(ui->simBut, &QPushButton::clicked, this, &QWidget::close);
}


void MainWindow::on_button_delete_all_clicked()
{
    // Once you have clicked on the "Delete All" button, all creatures (plants, omnivorous or herbivore) will be deleted from creature_list.
        ListWidget* creature_list = ui->groupBox_2->findChild<ListWidget*>();
        creature_list->clear();
        num_pred = 0;
        num_plant = 0;
        num_prey = 0;

        // Hide the Simulation button, called "simbut" for short, as you can't launch the simulation with no creatures.
        ui->simBut->setVisible(false);
        ui->groupBox->setVisible(false);
    }


    void MainWindow::on_button_delete_creature_clicked()
    {
        // Once you have clicked on the "Delete Creature" button, the selected creature in creature_list will be deleted.
        // We purposely didn't change the following creature's number, to have the user keep track of the property selection he/she chose for each creature.
        // Ex: you have in the creature_list "Plant 1", "Plant 2", "Plant 3", and you delete "Plant 2", then you will have "Plant 1" and "Plant 3" left in the list
        // and not "Plant 1" et "Plant 2" (which is "Plant 3" renamed as "Plant 2").

        ListWidget* creature_list = ui->groupBox_2->findChild<ListWidget*>();

        QListWidgetItem *it = creature_list->takeItem(creature_list->currentRow());
            delete it;

        // If the user used this button to delete all creatures from his list, then we hide the Simulation button, called "simbut" for short, as you can't launch the simulation with no creatures.

        int count = creature_list->count();
        if (count == 0) {
            ui->simBut->setVisible(false);
            ui->groupBox->setVisible(false);
        }
    }


    void MainWindow::on_button_rdm_clicked()
    {

        // Once you have clicked on the "Random" button, called button_rdm, the properties of your selected creature will be put at random values.

        ui->eat_creature->setCheckState(Qt::Unchecked);
        ui->eat_plant->setCheckState(Qt::Unchecked);
        ui->P_strength_n->setValue(((int) QRandomGenerator::global()->generate()) % 101);
        ui->eye_sight_n->setValue(((int) QRandomGenerator::global()->generate()) % 101);
        ui->max_energy_n->setValue(((int) QRandomGenerator::global()->generate()) % 101);
        ui->size_n->setValue(((int) QRandomGenerator::global()->generate()) % 101);
        ui->max_health_n->setValue(((int) QRandomGenerator::global()->generate()) % 101);
        ui->visibility_n->setValue(((int) QRandomGenerator::global()->generate()) % 101);

        int val = ((int) QRandomGenerator::global()->generate()) % 3;
        if (val == 0) {
            ui->eat_creature->setCheckState(Qt::Checked);
        }
        else if (val == 1) {
            ui->eat_creature->setCheckState(Qt::Checked);
            ui->eat_plant->setCheckState(Qt::Checked);
        }
        else if (val == 2) {
            ui->eat_plant->setCheckState(Qt::Checked);
        }
    }


    void MainWindow::on_button_reset_clicked()
    {

        // Once you have clicked on the "Reset" button, called button_reset, all the properties of your selected creature will be set back to zero.

        ui->eat_creature->setCheckState(Qt::Unchecked);
        ui->eat_plant->setCheckState(Qt::Unchecked);
        ui->P_strength_n->setValue(0);
        ui->eye_sight_n->setValue(0);
        ui->max_energy_n->setValue(0);
        ui->size_n->setValue(0);
        ui->max_health_n->setValue(0);
        ui->visibility_n->setValue(0);
    }
