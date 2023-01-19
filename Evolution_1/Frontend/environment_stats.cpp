#include "environment_stats.h"


Environment_Stats::Environment_Stats(SimulationView* menu, QWidget *parent): QChartView(parent) {

    set_menu(menu);
    set_env( menu->get_environment());
    startTimer(10000); //please do not remove this otherwise the chart will not update

    //chart1:
    //QScatterSeries *LBs = new QScatterSeries();
    //QScatterSeries *Creatures = new QScatterSeries();
    //QScatterSeries *Plants = new QScatterSeries();

    //chart2:
    //QBarSet *alive = new QBarSet("alive");
    //QBarSet *dead = new QBarSet("dead");
    //QBarSet *tn = new QBarSet("total_number");

    //chart2:
    //*alive << number_LBs_alive << number_creatures_alive << number_plants_alive;
    //*dead <<number_LBs_dead << number_creatures_dead << number_plants_dead;
    //*tn << number_LBs << number_creatures << number_plants;

    //charts 2,3:
    QBarSeries *series = new QBarSeries();


    //chart2:
    //series->append(alive);
    //series->append(dead);
    //series->append(tn);

    //chart1:
    //LBs->append(0, number_LBs);
    //Creatures->append(1, number_creatures);
    //Plants->append(2, number_plants);

    //all charts:
    chart = get_chart();
    setChart(chart);
    //?
    //*chart->advance(int phase)

    //charts 2,3:
    chart->addSeries(series);

    //chart1:
    //chart->addSeries(LBs);
    //chart->addSeries(Creatures);
    //chart->addSeries(Plants);
    //chart->createDefaultAxes();

    //charts 1 , 2:
    //chart->setTitle("Number of LBs, Creatures and Plants (for now update every 10 sec, problem with dead counter)");

    //charts 2,3:
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;

    //chart2:
    //categories << "LBs" << "Creatures" << "Plants";

    //chart3:
    categories << "0 to 20%" << "21% to 40%" << "41% to 60%" << "61% to 80%" << "81% to 100%";

    //charts 2,3:
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    set_x_axis(axisX);
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    set_y_axis(axisY);
    axisY->setRange(0,200);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    //all charts:
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    this->setRenderHint(QPainter::Antialiasing);
    show();

};

void Environment_Stats::timerEvent(QTimerEvent *event) {
    //std::cout << "timer event received" <<std::endl;
    update_chart();
}

void Environment_Stats::update_chart(){

    //For some reason only plants show up for now on the chart
    //chart 2
    /*number_LBs = 0;
    number_LBs_alive = 0;
    number_LBs_dead = 0;
    number_creatures = 0;
    number_creatures_alive = 0;
    number_creatures_dead = 0;
    number_plants = 0;
    number_plants_alive = 0;
    number_plants_dead = 0;

    //now updating every counter using the list
    QList<QGraphicsItem *> list_LBs = (this->env)->items();
    for (int i=0; i < list_LBs.count(); i++) {
        LivingBeing* LB = dynamic_cast<LivingBeing*>(list_LBs[i]);
        if (LB->get_type() == Creature::plant) {
            number_plants ++;
            number_LBs ++;
            if (LB->get_alive() == true) {
                number_plants_alive ++;
                number_LBs_alive++;}
            else {number_plants_dead++;
                  number_LBs_dead++;} }
        else if (LB->get_type() == Creature::creature) {
            number_creatures++;
            number_LBs++;
            if (LB->get_alive() == true) {
                number_creatures_alive ++;
                number_LBs_alive ++;}
            else {
                number_creatures_dead ++;
                number_LBs_dead ++;}
        }
    }

    */

    //all charts
    chart = get_chart();
    chart->removeAllSeries();
    QBarSeries *series = new QBarSeries();

    //chart 2
    /*QBarSet *alive = new QBarSet("alive");
    QBarSet *dead = new QBarSet("dead");
    QBarSet *tn = new QBarSet("total_number");
    *alive << number_LBs_alive << number_creatures_alive << number_plants_alive;
    *dead <<number_LBs_dead << number_creatures_dead << number_plants_dead;
    *tn << number_LBs << number_creatures << number_plants;*/
    /*series->append(alive);
    series->append(dead);
    series->append(tn);*/

    //chart 3:
    //for now I put random values in proportion because no LBs in the environment
    //but when there will be, prop should have the five numbers n1 ,..,n5 multiplied by 10 to see them more clearly bcse they are ratios between 0 and 1
    //chart3:
    QBarSet *prop = new QBarSet("number of creatures having ...% of their max_energy");
    std::vector<double> v = creature_energy_ratio();
    for (std::vector<double>::iterator j=v.begin();j!=v.end(); j++) {
        prop->append((*j));
        std::cout << (*j) << std::endl;
    }
    series->append(prop);
    chart->addSeries(series);
    series->attachAxis(get_x_axis());
    series->attachAxis(get_y_axis());
    update();
}



Environment_Stats::~Environment_Stats() {};

std::map<Creature::Enum_parameters, double> Environment_Stats::average_creatures(){
//    enum Enum_parameters{ physical_strength, Max_energy, eye_sight, visibility, eat_creature, eat_plants, Max_hp, size, last};
    std::map<Creature::Enum_parameters, double> param_average;
    QList<QGraphicsItem *> list = env->items();
    QListIterator<QGraphicsItem*> i(list);
    int count = 0;
    while (i.hasNext()){
        count ++;
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            for ( Creature::Enum_parameters param = (Creature::Enum_parameters)0; param != Creature::last; param=(Creature::Enum_parameters)(param+1) ) {
                param_average[param] = param_average[param] + c->get_parameter(param);
            }
        }
    }
    for ( Creature::Enum_parameters param = (Creature::Enum_parameters)0; param != Creature::last; param=(Creature::Enum_parameters)(param+1) ){
        param_average[param] = param_average[param] / count ;
    }
    return param_average;
}

std::map<Creature::Enum_parameters, double> Environment_Stats::average_prey(){
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


std::map<Creature::Enum_parameters, double> Environment_Stats::average_predator(){
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

void Environment_Stats::average_lifespan(int age){
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

std::vector<double> Environment_Stats::creature_energy_ratio() {
    std::vector<double> v;    //v stores the ratio of hp/max_hp for each creature
    QList<QGraphicsItem *> list = get_env()->items();
    QListIterator<QGraphicsItem*> i(list);
    while (i.hasNext()) {
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            double ratio = (c->get_energy())/(c->get_Max_energy());
            v.push_back(ratio);
        }
    }
    std::vector<double> res;  //res stores 5 numbers, the number of creatures having:
    double n1=0;   //between 0 and 20% of max_hp
    double n2=0;   //between 21% and 40% of max_hp
    double n3=0;   //between 41% and 60% of max_hp
    double n4=0;   //between 61% and 80% of max_hp
    double n5=0;   //between 81% and 100% of max_hp
    double total_nb=0;  //total nb of creatures stored in the vector v
    for (std::vector<double>::iterator j=v.begin();j!=v.end(); j++) {
        total_nb++;
        //std::cout<< (*j) << std::endl;
        if (0.0<=(*j)<0.2){
            n1+=1;}
        else if (0.2<=(*j)<0.4){
            n2+=1;}
        else if (0.4<=(*j)<0.6){
            n3+=1;}
        else if (0.6<=(*j)<0.8) {
            n4+=1;}
        else if (0.8<=(*j)<=1.0){
            n5+=1;}
    }
    std::cout <<"total nb of creatures : " << total_nb << std::endl;
    res.push_back(n1);
    res.push_back(n2);
    res.push_back(n3);
    res.push_back(n4);
    res.push_back(n5);
    return res;
};

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



void Environment_Stats2::update_chart(){
    //get the data from matei's average function
    //series->append(prop);
    //chart->addSeries(series);
    //series->attachAxis(get_x_axis());
    //series->attachAxis(get_y_axis());
    update();
}

Environment_Stats2::~Environment_Stats2() {};






/// AVERAGE PARAMETERS
Average_param::Average_param(SimulationView* menu, QWidget *parent): QChartView(parent) {
    set_t(0);
    set_menu(menu);
    set_env( menu->get_environment());
    startTimer(5000);

    /*//Creating the graph
    static std::map<Creature::Enum_parameters, QLineSeries*> series;
    //creates a different series for each parameter
    for (Creature::Enum_parameters param = (Creature::Enum_parameters)0; param != Creature::last; param=(Creature::Enum_parameters)(param+1))
            {
                QLineSeries *lineSeries = new QLineSeries();
                lineSeries->setName(Creature::name_param(param));
                series[param] = lineSeries;
                chart->addSeries(lineSeries);
            }
    */
    QLineSeries* series = new QLineSeries();
    chart = get_chart();
    setChart(chart);
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QValueAxis* axisX = new QValueAxis();
    set_x_axis(axisX);
    axisX->setMax(50);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    set_y_axis(axisY);
    axisY->setRange(0,200);
    axisX->setTitleText("1 unit : 1 update per 5 sec");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->setTitle("Evolution of the average size of predators/ preys");
    set_series(series);
    //all charts:
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    this->setRenderHint(QPainter::Antialiasing);
    update();
    show();

};

double Average_param::get_size_avg(){
    //enum Enum_parameters{ physical_strength, Max_energy, eye_sight, visibility, eat_creature, eat_plants, Max_hp, size, last};
    QList<QGraphicsItem *> list = get_env()->items();
    QListIterator<QGraphicsItem*> i(list);
    int counter = 0;
    double Size = 0;
    while(i.hasNext()){
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            counter++;
            Size += c->get_size();
        }
    }
    return Size/counter;
}


Average_param::~Average_param() {};

void Average_param::timerEvent(QTimerEvent *event) {
    //std::cout << "timer event received" <<std::endl;
    update_chart();
}


void Average_param::update_chart(){
    increase_t();
    chart = get_chart();
    series = get_series();
    series->append(get_t(), get_size_avg());
    update();
}
