#include "plant.h"
#include "living_being.h"
#include "creature.h"
#include "qpainter.h"
#include<cmath>



int N_Plants = 0;
//int number_plants = 0;
//int number_plants_alive = 0;
//int number_plants_dead = 0;

Plant::Plant():LivingBeing(){
    N_Plants+=1;
    //we need a way to differenciate animals and plants
    color = QColorConstants::DarkGreen;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        double val = abs((double)rand()/(double)RAND_MAX * 200);
        this->parameters.insert(std::pair<Enum_parameters, double>(param, val));
    }
    type = plant;
    this->set_hp(this->get_Max_hp());
    }


Plant::Plant(Environment *e): Plant(){
    this->set_scene(e);
}

Plant::Plant(std::map<Enum_parameters, double> parameters, Environment *e): Plant(e) {
    this->parameters = parameters;
    this->base_parameters = parameters; //we save "dna"
    //To be sure there are no excess:
    if (this->get_size()>200){
        this->set_size(200);
    }
    else if (this->get_size()<20){
        this->set_size(20); //we need plants to be pretty big in order for prey to survive
    }
}

Plant::~Plant() {
    N_Plants-=1;
};


/* No need normally since we have already a function with parameter, normally there is reproduction_rate in trhose parameters
Plant::Plant(double reproduction_rate) {
    this-> reproduction_rate = reproduction_rate;
    type = plant; }
*/


void Plant::die() {
    if ((!this->get_alive()) || (this->get_hp() <= 0) ) {

        set_alive(false);
        //here we chose to kill and destroy everything which is dead
        delete this;
    }};

void Plant::is_eaten(Creature &c) {

    //modifying the eater's attributes:


    double alpha = get_alpha(c);
    if (type_plant == 0) { // carbs
        c.set_energy(c.get_energy() + alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);}

    else if (type_plant == 1) { //protein
            c.set_physical_strength(c.get_physical_strength() + alpha);
            c.set_energy(c.get_energy() - alpha);}

    else if (type_plant == 2) { //slimming_effects
        c.set_eye_sight(c.get_eye_sight() + alpha);
        c.set_visibility(c.get_visibility() - alpha);}

    else if (type_plant == 3) { //allergenic_effect
        c.set_visibility(c.get_visibility() + alpha);
        c.set_eye_sight(c.get_eye_sight() - alpha);}

    else if (type_plant == 4) { // allergenic_protein
        c.set_physical_strength(c.get_physical_strength() + 2*alpha);
        c.set_energy(c.get_energy() - alpha);
        c.set_eye_sight(c.get_eye_sight() - alpha);}

    else if (type_plant == 5) { //allergenic_carbs
        c.set_energy(c.get_energy() + 2*alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
        c.set_eye_sight(c.get_eye_sight() - alpha);}

    else if (type_plant == 6) { //slimming_protein
        c.set_physical_strength(c.get_physical_strength() + 2*alpha);
        c.set_energy(c.get_energy() - alpha);
        c.set_visibility(c.get_visibility() - alpha);}

    else if (type_plant == 7) { //slimming_carbs
        c.set_energy(c.get_energy() + 2*alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
        c.set_visibility(c.get_visibility() - alpha);}


    //damage to the plant:

    double size_coef = 0.25*(c.get_size()/get_size());
    set_size(get_size() - size_coef );
    double dmg_coef = 0.25*(c.get_hp()/get_hp());
    take_dmg(dmg_coef);
}


void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::white);

    //This is the coefficient we'll divide everything by /200 because size can be at most 200 and by 2 because it seems more appropriated
    double k =  get_size()/(200 * 10);

    painter->drawEllipse(QRectF(-25*k,-25*k,25*k,25*k));
    painter->drawEllipse(QRectF(0,0,25*k,25*k));
    painter->drawEllipse(QRectF(-25*k,0,25*k,25*k));
    painter->drawEllipse(QRectF(0,-25*k,25*k,25*k));
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(QRectF(-15*k,-15*k,30*k,30*k));


    //qreal adjust = 0.5;
    //painter->drawRect((-22 - adjust)*k, (-22 - adjust)*k, (45 + adjust)*k, (45 + adjust)*k);
}

QRectF Plant::boundingRect() const
{

    double k = get_size()/(200 * 6);

    qreal adjust = 0.5;
    return QRectF((-22 - adjust)*k, (-22 - adjust)*k, (45 + adjust)*k, (45 + adjust)*k);
}


void Plant::set_reproduction_rate(double rr){this->parameters[reproduction_rate] = rr;}
double Plant::get_reproduction_rate(){return this->parameters[reproduction_rate];}
void Plant::set_size(double s){this->parameters[size] = s;}
double Plant::get_size() const {return this->parameters.at(size);}
void Plant::set_Max_hp(double ms){this->parameters[Max_hp] = ms;}
double Plant::get_Max_hp() const{return this->parameters.at(Max_hp);}
void Plant::set_hp(double ms){this->hp = ms;}
double Plant::get_hp() const{return this->hp;}
double Plant::get_Max_size() const{return this->parameters.at(Max_size);}
void Plant::set_Max_size(double s) {this->parameters[Max_size]=s;}






void Plant::take_dmg(double dmg){
    this->set_hp(this->get_hp() - dmg);
}


double Plant::get_alpha(Creature &c) {
    double ps = get_size();
    double cs = c.get_size();
    double d = ps - cs;
    double dif = abs(d);
    double alpha = 1 - (1/dif);
    return alpha;
}
void Plant::carbs(Creature &c) {
    if (type_plant == 0) {
        double alpha = get_alpha(c);

        c.set_energy(c.get_energy() + alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
    };

};


void Plant::protein(Creature &c){
    if (type_plant == 1) {
        double alpha = get_alpha(c);


        c.set_physical_strength(c.get_physical_strength() + alpha);
        c.set_energy(c.get_energy() - alpha);
    };


};

void Plant::slimming_effect(Creature &c){
    if (type_plant == 2) {
    double alpha = get_alpha(c);


    c.set_eye_sight(c.get_eye_sight() + alpha);
    c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::allergenic_effect(Creature &c){
    if (type_plant == 3) {
    double alpha = get_alpha(c);


    c.set_visibility(c.get_visibility() + alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);

    };

};

void Plant::allergenic_protein(Creature &c) {
    if (type_plant == 4) {
    double alpha = get_alpha(c);

    c.set_physical_strength(c.get_physical_strength() + 2*alpha);
    c.set_energy(c.get_energy() - alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);
    };

};

void Plant::allergenic_carbs(Creature &c){
    if (type_plant == 5) {
    double alpha = get_alpha(c);


    c.set_energy(c.get_energy() + 2*alpha);
    c.set_physical_strength(c.get_physical_strength() - alpha);
    c.set_eye_sight(c.get_eye_sight() - alpha);
    };

};

void Plant::slimming_protein(Creature &c) {
    if (type_plant == 6) {
    double alpha = get_alpha(c);


    c.set_physical_strength(c.get_physical_strength() + 2*alpha);
    c.set_energy(c.get_energy() - alpha);
    c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::slimming_carbs(Creature &c) {
    if (type_plant == 7) {
        double alpha = get_alpha(c);


        c.set_energy(c.get_energy() + 2*alpha);
        c.set_physical_strength(c.get_physical_strength() - alpha);
        c.set_visibility(c.get_visibility() - alpha);
    };

};

void Plant::playstep() {    // random values for increasing hp, random weight of growing coef for increasing size
    //changing size and upper bound it by max_size , same for hp



    repro_factor+=rand()%5;

    if (repro_factor>=500){
        repro_factor -= 500;
        if (N_Plants<250){
            Plant* p = reproduction();
            this->get_scene()->addItem(p);
        }
    }

    increase_alive_time();
    double growing_coef = 0.25 * get_Max_size()/get_size();

    if (get_size()< get_Max_size()) {
        double new_size = get_size()+ growing_coef;
        set_size(new_size);}
    if (get_size()>get_Max_size()) {
        set_size(get_Max_size());

    if (get_hp()< get_Max_hp()){
        set_hp(1.1*get_hp()); }
    if (get_hp()>get_Max_hp()) {
        set_hp(get_Max_hp()); }
}
};


Plant* Plant::reproduction(){
    std::map<Enum_parameters, double> param_new_plant;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        double val = normal_distrib(parameters[param],0.1);
        param_new_plant.insert(std::pair<Enum_parameters, float>(param, val));
    }
    Plant* p = new Plant(param_new_plant, this->get_scene());
    p->setPos(this->x() + 200*(double)rand()/(double)(RAND_MAX),this->y()+200*(double)rand()/(double)(RAND_MAX));

    //(The only moment a plant can use this is when it's borned)
    //PACMAN, when touching a border, the creature is TPed on the other side, however this is not exactly how the border of pacman works... (is is continuous)
    if (p->x()<0){
        p->setX(500+x());
        p->setY(500-y());
    }
    if (p->y()<0){
        p->setX(500-x());
        p->setY(500+y());
    }
    if (p->x()>500){
        p->setX(500-x());
        p->setY(500-y());
    }
    if (p->y()>500){
        p->setX(500-x());
        p->setY(500-y());
    }

    return p;
}


