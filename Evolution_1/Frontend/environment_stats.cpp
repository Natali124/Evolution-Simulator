#include "environment_stats.h"


Energy_perc::Energy_perc(SimulationView* menu, QWidget *parent): QChartView(parent) {
    set_t(0);
    set_menu(menu);
    set_env( menu->get_environment());
    startTimer(5000);

    QLineSeries* series_prey_min = new QLineSeries();
    QLineSeries* series_prey_plus = new QLineSeries();
    QLineSeries* series_predator_min = new QLineSeries();
    QLineSeries* series_predator_plus = new QLineSeries();

    series_prey_min->setName("preys, less ");
    series_prey_min->setColor("cyan");
    series_prey_plus->setName("preys, more ");
    series_prey_plus->setColor("orange");
    series_predator_min->setName("predators, less ");
    series_predator_min->setColor("magenta");
    series_predator_plus->setName("predator, more ");
    series_predator_plus->setColor("red");
    chart = get_chart();
    setChart(chart);
    chart->addSeries(series_prey_min);
    chart->addSeries(series_prey_plus);
    chart->addSeries(series_predator_min);
    chart->addSeries(series_predator_plus);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis* axisX = new QValueAxis();
    set_x_axis(axisX);
    axisX->setMax(50);
    chart->addAxis(axisX, Qt::AlignBottom);
    series_prey_min->attachAxis(axisX);
    series_prey_plus->attachAxis(axisX);
    series_predator_min->attachAxis(axisX);
    series_predator_plus->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    set_y_axis(axisY);
    axisY->setRange(0,100);
    axisX->setTitleText("1 unit : 1 update per 5 sec");
    chart->addAxis(axisY, Qt::AlignLeft);
    series_prey_min->attachAxis(axisY);
    series_prey_plus->attachAxis(axisY);
    series_predator_min->attachAxis(axisY);
    series_predator_plus->attachAxis(axisY);

    chart->setTitle("Evolution of the percentage of predators/preys having less/more than half of their max energy");
    set_series_prey_min(series_prey_min);
    set_series_prey_plus(series_prey_plus);
    set_series_predator_min(series_predator_min);
    set_series_predator_plus(series_predator_plus);
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    this->setRenderHint(QPainter::Antialiasing);
    update();
    show();

};

void Energy_perc::timerEvent(QTimerEvent *event) {
    //std::cout << "timer event received" <<std::endl;
    update_chart();
}

void Energy_perc::update_chart(){
    increase_t();
    chart = get_chart();
    series_prey_min = get_series_prey_min();
    series_prey_plus = get_series_prey_plus();
    series_prey_min->append(get_t(),creature_energy_ratio()[0]);
    series_prey_plus->append(get_t(),creature_energy_ratio()[1] );
    series_predator_min = get_series_predator_min();
    series_predator_plus = get_series_predator_plus();
    series_predator_min->append(get_t(), creature_energy_ratio()[2]);
    series_predator_plus->append(get_t(), creature_energy_ratio()[3]);
    update();
};

Energy_perc::~Energy_perc() {};

std::vector<double> Energy_perc::creature_energy_ratio() {
    std::vector<double> v;
    QList<QGraphicsItem *> list = get_env()->items();
    QListIterator<QGraphicsItem*> i(list);
    int counter_prey = 0;
    int counter_pred = 0;
    int nminprey = 0;
    int nplusprey =0;
    int nminpred =0;
    int npluspred=0;
    while(i.hasNext()){
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            double ratio = (c->get_energy())/(c->get_Max_energy());
            if (c->get_eat_plants()){
                counter_prey++;
                if (ratio<0.5){
                    nminprey++;
                }
                else if (0.5<=ratio && ratio<=1) {
                    nplusprey++;
                }
            }
            else if (c->get_eat_creature()){
                counter_pred++;
                if (ratio<0.5){
                    nminpred++;
                }
                else if (0.5<=ratio && ratio<=1) {
                    npluspred++;
                }
            }
        }
    }

    v.push_back((100*nminprey)/counter_prey);//to have percentage
    v.push_back((100*nplusprey)/counter_prey);
    v.push_back((100*nminpred)/counter_pred);//to have percentage
    v.push_back((100*npluspred)/counter_pred);
    return v;
}

Environment_Stats2::Environment_Stats2(SimulationView* menu, QWidget *parent): QChartView(parent) {

    //set_menu(menu);
    //set_env( menu->get_environment());
    //startTimer(10000); //please do not remove this otherwise the chart will not update

    chart = get_chart();
    setChart(chart);
    chart->setTitle("Dynamic chart of the average lifetime of the last 50 that died");

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    QLineSeries *LB_series = new QLineSeries();
    QLineSeries *Creature_series = new QLineSeries();
    QLineSeries *Plant_series = new QLineSeries();

    chart->addSeries(LB_series);
    chart->addSeries(Creature_series);
    chart->addSeries(Plant_series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QPen plant(Qt::green);
    plant.setWidth(3);
    Plant_series->setPen(plant);
    //Plant_series->append();

    QPen creature(Qt::red);
    creature.setWidth(3);
    Creature_series->setPen(creature);
    //Creature_series->append();

    QPen LB(Qt::blue);
    creature.setWidth(3);
    LB_series->setPen(LB);
    //LB_series->append();

    //QStringList categories;
    //categories << "0 to 20%" << "21% to 40%" << "41% to 60%" << "61% to 80%" << "81% to 100%";

    //QBarCategoryAxis* axisX = new QBarCategoryAxis();
    //axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    Plant_series->attachAxis(axisX);
    Plant_series->attachAxis(axisY);
    Creature_series->attachAxis(axisX);
    Creature_series->attachAxis(axisY);
    LB_series->attachAxis(axisX);
    LB_series->attachAxis(axisY);

    axisY->setRange(0,500);
    axisX->setRange(0, 10);
    //all charts:
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    this->setRenderHint(QPainter::Antialiasing);
    chart->show();

};


void Environment_Stats2::average_lifespan(int age){
    if (number_ages == 49) {
        last_50_ages[49] = age;
        number_ages = 0;
        int sum = 0;
        for(int i = 0; i < 50 ; i++){
              sum+= last_50_ages[i];
           }
        sum = sum / 50;

    }
    else {
        last_50_ages[number_ages] = age;
        number_ages++;
    }
}


std::map<Creature::Enum_parameters, double> Environment_Stats2::average_prey(){
//    enum Enum_parameters{ physical_strength, Max_energy, eye_sight, visibility, eat_creature, eat_plants, Max_hp, size, last};
    std::map<Creature::Enum_parameters, double> param_average;
    QList<QGraphicsItem *> list = env->items();
    QListIterator<QGraphicsItem*> i(list);
    int count = 0;
    while (i.hasNext()){
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            if (c->get_eat_plants() == true & c->get_eat_creature() == false){
                count ++;
                for ( Creature::Enum_parameters param = (Creature::Enum_parameters)0; param != Creature::last; param=(Creature::Enum_parameters)(param+1) ) {
                    param_average[param] = param_average[param] + c->get_parameter(param);
                }
            }
        }
    }
    for ( Creature::Enum_parameters param = (Creature::Enum_parameters)0; param != Creature::last; param=(Creature::Enum_parameters)(param+1) ){
        param_average[param] = param_average[param] / count ;
    }
    return param_average;
}


std::map<Creature::Enum_parameters, double> Environment_Stats2::average_predator(){
//    enum Enum_parameters{ physical_strength, Max_energy, eye_sight, visibility, eat_creature, eat_plants, Max_hp, size, last};
    std::map<Creature::Enum_parameters, double> param_average;
    QList<QGraphicsItem *> list = env->items();
    QListIterator<QGraphicsItem*> i(list);
    int count = 0;
    while (i.hasNext()){
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            if (c->get_eat_plants() == false & c->get_eat_creature() == true){
                count++;
                for ( Creature::Enum_parameters param = (Creature::Enum_parameters)0; param != Creature::last; param=(Creature::Enum_parameters)(param+1) ) {
                    param_average[param] = param_average[param] + c->get_parameter(param);
                }
            }
        }
    }
    for ( Creature::Enum_parameters param = (Creature::Enum_parameters)0; param != Creature::last; param=(Creature::Enum_parameters)(param+1) ){
        param_average[param] = param_average[param] / count ;
    }
    return param_average;
}


/*void Environment_Stats2::update_chart(){
    //get the data from matei's average function
    //series->append(prop);
    //chart->addSeries(series);
    //series->attachAxis(get_x_axis());
    //series->attachAxis(get_y_axis());
    update();
}
*/

Environment_Stats2::~Environment_Stats2() {};






/// AVERAGE SIZE
Average_size::Average_size(SimulationView* menu, QWidget *parent): QChartView(parent) {
    set_t(0);
    set_menu(menu);
    set_env( menu->get_environment());
    startTimer(5000);

    QLineSeries* series_prey = new QLineSeries();
    QLineSeries* series_predator = new QLineSeries();
    QLineSeries* series_plant = new QLineSeries();

    series_prey->setName("preys");
    series_prey->setColor("orange");
    series_predator->setName("predators");
    series_predator->setColor("red");
    series_plant->setColor("green");
    series_plant->setName("plants");
    chart = get_chart();
    setChart(chart);
    chart->addSeries(series_prey);
    chart->addSeries(series_predator);
    chart->addSeries(series_plant);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis* axisX = new QValueAxis();
    set_x_axis(axisX);
    axisX->setMax(50);
    chart->addAxis(axisX, Qt::AlignBottom);
    series_prey->attachAxis(axisX);
    series_predator->attachAxis(axisX);
    series_plant->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    set_y_axis(axisY);
    axisY->setRange(0,200);
    axisX->setTitleText("1 unit : 1 update per 5 sec");
    chart->addAxis(axisY, Qt::AlignLeft);
    series_prey->attachAxis(axisY);
    series_predator->attachAxis(axisY);
    series_plant->attachAxis(axisY);

    chart->setTitle("Evolution of the average size of predators, preys and plants");
    set_series_prey(series_prey);
    set_series_predator(series_predator);
    set_series_plant(series_plant);
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    this->setRenderHint(QPainter::Antialiasing);
    update();
    show();

};

std::vector<double> Average_size::get_size_avg(){ //returns a vector of doubles: 1st item is avg size of the preys, second is for predators,
    // third is for plants
    std::vector<double> v;
    QList<QGraphicsItem *> list = get_env()->items();
    QListIterator<QGraphicsItem*> i(list);
    int counter_prey = 0;
    int counter_predator = 0;
    int counter_plant =0;
    double Size_prey = 0;
    double Size_predator = 0;
    double Size_plant =0;
    while(i.hasNext()){
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            if (c->get_eat_plants()){
                counter_prey++;
                Size_prey += c->get_size();
            }
            else if (c->get_eat_creature()){
                counter_predator++;
                Size_predator += c->get_size();
            }
        }
        else if (type== Plant::plant) {
            Plant* p = dynamic_cast<Plant*>(LB);
            counter_plant++;
            Size_plant += p->get_size();
        }
    }
    v.push_back(Size_prey/counter_prey);
    v.push_back(Size_predator/counter_predator);
    v.push_back(Size_plant/counter_plant);
    return v;
}


Average_size::~Average_size() {};

void Average_size::timerEvent(QTimerEvent *event) {
    //std::cout << "timer event received" <<std::endl;
    update_chart();
}


void Average_size::update_chart(){
    increase_t();
    chart = get_chart();
    series_prey = get_series_prey();
    series_prey->append(get_t(), get_size_avg()[0]);
    series_predator = get_series_predator();
    series_predator->append(get_t(), get_size_avg()[1]);
    series_plant = get_series_plant();
    series_plant->append(get_t(), get_size_avg()[2]);
    update();
}


Alive_perc::Alive_perc(SimulationView* menu, QWidget *parent): QChartView(parent) {
    set_t(0);
    set_menu(menu);
    set_env( menu->get_environment());
    startTimer(5000);

    QLineSeries* series_prey = new QLineSeries();
    QLineSeries* series_predator = new QLineSeries();
    QLineSeries* series_plant = new QLineSeries();

    series_prey->setName("preys");
    series_prey->setColor("orange");
    series_predator->setName("predators");
    series_predator->setColor("red");
    series_plant->setColor("green");
    series_plant->setName("plants");
    chart = get_chart();
    setChart(chart);
    chart->addSeries(series_prey);
    chart->addSeries(series_predator);
    chart->addSeries(series_plant);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis* axisX = new QValueAxis();
    set_x_axis(axisX);
    axisX->setMax(50);
    chart->addAxis(axisX, Qt::AlignBottom);
    series_prey->attachAxis(axisX);
    series_predator->attachAxis(axisX);
    series_plant->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    set_y_axis(axisY);
    axisY->setRange(0,100);
    axisX->setTitleText("1 unit : 1 update per 5 sec");
    chart->addAxis(axisY, Qt::AlignLeft);
    series_prey->attachAxis(axisY);
    series_predator->attachAxis(axisY);
    series_plant->attachAxis(axisY);

    chart->setTitle("Percentage of alive predators, preys and plants among Living Beings");
    set_series_prey(series_prey);
    set_series_predator(series_predator);
    set_series_plant(series_plant);
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    this->setRenderHint(QPainter::Antialiasing);
    update();
    show();

};

std::vector<double> Alive_perc::get_alive_perc(){ //returns a vector of doubles: 1st item is avg size of the preys, second is for predators,
    // third is for plants
    std::vector<double> v;
    QList<QGraphicsItem *> list = get_env()->items();
    QListIterator<QGraphicsItem*> i(list);
    int counter_prey = 0;
    int counter_predator = 0;
    int counter_plant =0;
    int counter_LB =0;
    while(i.hasNext()){
        counter_LB++;
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            if (c->get_eat_plants()){
                counter_prey++;
            }
            else if (c->get_eat_creature()){
                counter_predator++;
            }
        }
        else if (type== Plant::plant) {
            Plant* p = dynamic_cast<Plant*>(LB);
            counter_plant++;
        }
    }
    v.push_back((100*counter_prey)/counter_LB);
    v.push_back((100*counter_predator)/counter_LB);
    v.push_back((100*counter_plant)/counter_LB);
    return v;
}


Alive_perc::~Alive_perc() {};

void Alive_perc::timerEvent(QTimerEvent *event) {
    //std::cout << "timer event received" <<std::endl;
    update_chart();
}


void Alive_perc::update_chart(){
    increase_t();
    chart = get_chart();
    series_prey = get_series_prey();
    series_prey->append(get_t(), get_alive_perc()[0]);
    series_predator = get_series_predator();
    series_predator->append(get_t(), get_alive_perc()[1]);
    series_plant = get_series_plant();
    series_plant->append(get_t(), get_alive_perc()[2]);
    update();
}

