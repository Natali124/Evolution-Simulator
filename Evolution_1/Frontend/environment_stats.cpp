#include "environment_stats.h"
#include "creature.h"


Environment_Stats::Environment_Stats(SimulationView& menu, QWidget *parent): QChartView(parent)
{

    this->startTimer(10000);



    this->env = menu.get_environment();


    //chart1:
    //QScatterSeries *LBs = new QScatterSeries();
    //QScatterSeries *Creatures = new QScatterSeries();
    //QScatterSeries *Plants = new QScatterSeries();

    //chart2:
    QBarSet *alive = new QBarSet("alive");
    QBarSet *dead = new QBarSet("dead");
    QBarSet *tn = new QBarSet("total_number");

    //chart3:
    //QBarSet *prop = new QBarSet("proportion of creatures having ...% of their max_hp  (random for now, working on it)");

    //chart2:
    *alive << number_LBs_alive << number_creatures_alive << number_plants_alive;
    *dead <<number_LBs_dead << number_creatures_dead << number_plants_dead;
    *tn << number_LBs << number_creatures << number_plants;

    //charts 2,3:
    QBarSeries *series = new QBarSeries();

    //chart 3:
    //for now I put random values in proportion because no LBs in the environment
    //but when there will be, prop should have the five numbers n1 ,..,n5 multiplied by 10 to see them more clearly bcse they are ratios between 0 and 1
    //std::vector<double> v = creature_hp_ratio(menu);
    //for (std::vector<double>::iterator j=v.begin();j!=v.end(); j++) {
    //    prop->append((*j)*10);
    //}
    //*prop << 3.1 << 1.0 << 3.2 << 1.7 << 1.0 ;
    //series->append(prop);

    //chart2:
    series->append(alive);
    series->append(dead);
    series->append(tn);

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
    chart->setTitle("Number of LBs, Creatures and Plants (for now update every 10 sec, problem with dead counter)");

    //charts 2,3:
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;

    //chart2:
    categories << "LBs" << "Creatures" << "Plants";

    //chart3:
    //categories << "0 to 20%" << "21% to 40%" << "41% to 60%" << "61% to 80%" << "81% to 100%";

    //charts 2,3:
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,15);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    //all charts:
    chart->legend()->setVisible(true);;
    chart->legend()->setAlignment(Qt::AlignBottom);
    this->setRenderHint(QPainter::Antialiasing);
    update();
    repaint();
    show();

};

void Environment_Stats::timerEvent(QTimerEvent *event) {
    //std::cout << "timer event received" <<std::endl;
    update_chart();
}

void Environment_Stats::update_chart(){
    chart = get_chart();
    chart->removeAllSeries();
    QBarSet *alive = new QBarSet("alive");
    QBarSet *dead = new QBarSet("dead");
    QBarSet *tn = new QBarSet("total_number");
    *alive << number_LBs_alive << number_creatures_alive << number_plants_alive;
    *dead <<number_LBs_dead << number_creatures_dead << number_plants_dead;
    *tn << number_LBs << number_creatures << number_plants;
    QBarSeries *series = new QBarSeries();
    series->append(alive);
    series->append(dead);
    series->append(tn);
    chart->addSeries(series);
    update();
}

void Environment_Stats::average_creatures(SimulationView& menu){
//    enum Enum_parameters{ physical_strength, Max_energy, eye_sight, visibility, eat_creature, eat_plants, Max_hp, size, last};
    std::map<Creature::Enum_parameters, double> param_average;
    Environment* environment = menu.get_environment();
    QList<QGraphicsItem *> list = environment->items();
    QListIterator<QGraphicsItem*> i(list);
    while (i.hasNext()){
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
//            double ratio = (c->get_hp())/(c->get_Max_hp());
            for ( Creature::Enum_parameters param = (Creature::Enum_parameters)0; param != Creature::last; param=(Creature::Enum_parameters)(param+1) ) {
                Creature* c = dynamic_cast<Creature*>(LB);
                param_average[param] = param_average[param] + c->get_parameter(param);
//                double val = normal_distrib(parameters[param], 0.1); // 0.1 is arbitrary value
//                param_new_creature.insert(std::pair<Enum_parameters, double>(param, val));
            }
        }
    }

}


Environment_Stats::~Environment_Stats() {};

std::vector<double> creature_hp_ratio(SimulationView& menu) {
    std::vector<double> v;    //v stores the ratio of hp/max_hp for each creature
    Environment* environment = menu.get_environment();
    QList<QGraphicsItem *> list = environment->items();
    QListIterator<QGraphicsItem*> i(list);
    while (i.hasNext()) {
        LivingBeing* LB = dynamic_cast<LivingBeing*>(i.next());
        LivingBeing::Type_LB type = LB->get_type();
        if (type == Creature::creature) {
            Creature* c = dynamic_cast<Creature*>(LB);
            double ratio = (c->get_hp())/(c->get_Max_hp());
            v.push_back(ratio);
        }
    }
    std::vector<double> res;  //res stores 5 numbers, the proportion of creatures having:
    double n1=0;   //between 0 and 20% of max_hp
    double n2=0;   //between 21% and 40% of max_hp
    double n3=0;   //between 41% and 60% of max_hp
    double n4=0;   //between 61% and 80% of max_hp
    double n5=0;   //between 81% and 100% of max_hp
    double total_nb=0;  //total nb of creatures stored in the vector v
    for (std::vector<double>::iterator j=v.begin();j!=v.end(); j++) {
        total_nb+=1;
        if (0.0<=(*j)<=0.2){
            n1+=1;    }
        else if (0.21<=(*j)<=0.4){
            n2+=1;}
        else if (0.41<=(*j)<=0.6){
            n3+=1;}
        else if (0.61<=(*j)<=0.8) {
            n4+=1;}
        else if (0.81<=(*j)<=1.0){
            n5+=1;}
    }
    double n1_f = n1/total_nb;
    double n2_f = n2/total_nb;
    double n3_f = n3/total_nb;
    double n4_f = n4/total_nb;
    double n5_f = n5/total_nb;
    res.push_back(n1_f);
    res.push_back(n2_f);
    res.push_back(n3_f);
    res.push_back(n4_f);
    res.push_back(n5_f);
    return res;
};


