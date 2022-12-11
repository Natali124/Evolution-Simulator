#include <random>
#include "creature.h"
#include "Neural_Network/network.hpp"
#include "plant.h"
#include "living_being.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <QGraphicsItem>



using namespace std;

Other::Square::Square(): Square(0, 0, 0, 1, 1){
}
Other::Square::Square(qreal X, qreal Y, qreal R, qreal W, qreal H): w(W), h(H){
    setX(X); setY(Y), setRotation(R);
}
QRectF Other::Square::boundingRect() const{
    return QRectF(this->x(), this->y(), this->w, this->h);
}

//we don't want it to appear
void Other::Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
}

void Other::Square::set_shape(){
    QPainterPath path;
    path.addRect(this->boundingRect());
}




Creature::Creature():LivingBeing() {
    //we need a way to differenciate animals and plants
    color = QColorConstants::DarkGray;
    // in the iteration param refers to an int into Enum_parameters (which does not include the value last)
    for (Enum_parameters param = (Enum_parameters)0 ; param != last; param=(Enum_parameters)(param+1)) {
        double val = abs(1+(double)rand()/(double)(RAND_MAX)*200); // val is the random value that we will assign to val
        this->parameters.insert(std::pair<Enum_parameters, double>(param, val));
    };

    this->set_energy(this->get_Max_energy());
    this->set_hp(this->get_Max_hp());


    // the brain is already constructed by the default constructor in the .h file.
    type = creature;
    this->set_alive(true);
    found_food = false;
    counter_no_eat=0;
    counter_no_sleep=0;
}

Creature::Creature(std::map<Enum_parameters, double> parameters, Network brain): Creature() {
    this->parameters = parameters;
    this->base_parameters = parameters; //we save "dna"
    this->brain = brain;
}

Creature::~Creature() {}



LivingBeing* Creature::reproduction() {

    std::map<Enum_parameters, double> param_new_creature;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        double val = normal_distrib(parameters[param], 0.1); // 0.1 is arbitrary value
        param_new_creature.insert(std::pair<Enum_parameters, double>(param, val));
    }
    Network new_brain = Network();
    //Network new_brain = network(old brain);
    // modify this function when we can create new networks with inputs
    //new_brain.apply_on_all_edges(normal_distrib_random_edge);
    new_brain.apply_on_all_weights(normal_distrib_random());
    Creature* C= new Creature(param_new_creature, brain);
    return C;
};


std::vector<LivingBeing*> Creature::get_close(){
    std::vector<LivingBeing*> v;

    //This will be used to get all objects in front
    Other::Square *S = new Other::Square(this->x(), this->y(), this->rotation(), this->size, this->size);
    QList<QGraphicsItem*> list = S->collidingItems();
    foreach(QGraphicsItem* i , list)
    {
        LivingBeing *L = dynamic_cast<LivingBeing*>(i);
        // if i was possible to cast && if they don't have the same coordinates
        if ((L!=nullptr) && ((L->x() != this->x()) || (L->y() != this->y()))){
            v.push_back(L);
        }
    }
    delete S;


    return v;
}

void Creature::take_dmg(double dmg){
    this->set_hp(this->get_hp()-dmg);
}

void Creature::attack(){
    //we'll first split between creatures and plants:
    std::vector<LivingBeing*> Close = this->get_close();
    int len = Close.size();
    const double alpha_victim = 0.5; //we have to decide what coeff to give
    const double alpha_attacker = 0.05;
    //double mean = 0;
    double dmg = this->get_size()*this->get_physical_strength()*alpha_victim/len;
    for(vector<LivingBeing*>::iterator i = Close.begin(); i != Close.end(); i++){
        (*i)->take_dmg(dmg);
        //mean += (*i)->get_size()/len;
    }
    this->set_energy(get_energy() - this->get_size()*alpha_attacker);
    //we discussed the possibility of making the energy loss depend on the size of the other creatures
    // we could make the attack depend on the avg size of the creatures
}

void Creature::die() {if ((get_alive()) && (this->get_hp() == 0) ) {
        set_alive(false);}
                     };

void::Creature::is_eaten(Creature &c) {

    //damage to the victim:

    if (get_alive() == false) {
        double alpha;
        if(c.get_eat_creature() && c.get_eat_plants()){alpha = 0.8;}
        else{alpha=1;}
        double loss = alpha*c.get_size();
        double current_energy = get_energy();
        set_energy(current_energy - loss);
    };
};

//not done yet

//void Creature::move_away(){
//    //std::vector<LivingBeing*> Creature
//    const double coeff = 0.3; //by how much are they moving away
//    QList<QGraphicsItem*> list = this->collidingItems();
//    foreach(QGraphicsItem* i , list)
//    {
//        LivingBeing *L = dynamic_cast<LivingBeing*>(i);
//        if(typeid(Creature) == typeid(L)){
//            double xdiff = this->x() - L->x();
//            double ydiff = this->y() - L->y();
//            this->setX(x() + xdiff * coeff);

//        }
//    }
//}


void Creature::set_energy(double e){this->energy = e;}
double Creature::get_energy() const{return this->energy;}
void Creature::set_physical_strength(double ps){this->parameters[physical_strength] = ps;}
double Creature::get_physical_strength() const{return this->parameters.at(physical_strength);}
void Creature::set_eye_sight(double es){this->parameters[eye_sight] = es;}
double Creature::get_eye_sight() const{return  this->parameters.at(eye_sight);}
void Creature::set_visibility(double v){this->parameters[visibility] = v;}
double Creature::get_visibility() const{return this->parameters.at(visibility);}
void Creature::set_Max_energy(double me){this->parameters[Max_energy] = me;}
double Creature::get_Max_energy() const{return this->parameters.at(Max_energy);}
bool Creature::get_eat_creature(){return this->parameters[eat_creature];}
bool Creature::get_eat_plants(){return this->parameters[eat_plants];}
int Creature::get_digest_time(){return this->digest_time;}
void Creature::set_digest_time(int time){this->digest_time = time;}
vector<double> Creature::get_food_attributes() {return this->food_attributes;}
 //void Creature::set_food(LivingBeing &f){this->food = f;}
void Creature::set_size(double s){this->parameters[size] = s;}
double Creature::get_size() const{return this->parameters.at(size);}
void Creature::set_hp(double s){this->hp = s;}
double Creature::get_hp(){return this->hp;}
void Creature::set_Max_hp(double mh){this->parameters[Max_hp] = mh;}
double Creature::get_Max_hp() const{return this->parameters.at(Max_hp);}
bool Creature::get_found_food() {return this->found_food;}
void Creature::set_found_food(bool b) {this->found_food = b;}
int Creature::get_counter_no_sleep() {return this->counter_no_sleep;}
int Creature::get_counter_no_eat() {return this->counter_no_eat;}
void Creature::set_counter_no_eat(int i) {this->counter_no_eat = i;}
void Creature::set_counter_no_sleep(int j){this->counter_no_sleep = j;}


void Creature::bound_energy_hp() {
    if (get_energy()>get_Max_energy()) {
        set_energy(get_Max_energy());}
    if (get_hp()>get_Max_hp()) {
        set_hp(get_Max_hp());}
}

void Creature::normal_distrib_random_edge(Edge& edge){
    //takes an edge and has a 10% percent chance to modify the weight according to the normal distribuition.
    double parameter = edge.get_weight();
    double p = abs((double)rand()/(double)RAND_MAX);
    if (p < 0.1){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> d(parameter, 0.1);
        edge.set_weight(d(gen));
    }
}

std::function<double(double)> Creature::normal_distrib_random(){ return [](double weight){
    //takes an weight of an edge and has a 10% percent chance to modify the weight according to the normal distribuition.
    double p = abs((double)rand()/(double)RAND_MAX);
    if (p < 0.1){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> d(weight, 0.1);
        weight = d(gen);
    }
    return weight;
};}


/*
Creature::Creature() {physical_strength=0;energy=0;eye_sight=0;visibility=0;brain = Network();}
Creature::Creature(double physical_strength,double energy, double eye_sight, double visibility, Network brain) {
this-> physical_strength = physical_strength,
this-> energy=energy,this->eye_sight= eye_sight,this-> visibility=visibility,this-> brain=brain; };
*/

//input_vector : (sleep, eat, attack, move, sleep_time, eat_time, move_rotate, move_distance)
void Creature::decision(vector<double>input_vector){
    double action = *max_element(input_vector.begin(), input_vector.begin()+4);
    int j = 0;
    for (vector<double>::iterator i=input_vector.begin(); i!=input_vector.begin()+4; i++){
        if (action==*i) {break;}
        j++;
        }
    if(j==0){
        sleep(*(input_vector.begin()+4)); //sleep for sleep_time
    }
    if(j==1){
        LivingBeing* food = find_food();
        if (get_found_food()) {
            eat((*food), *(input_vector.begin()+5));}
    }
    if(j==2){
        double rotation = *(input_vector.begin()+6);
        double distance = *(input_vector.begin()+7);
        move(rotation, distance);
    }

}


void Creature::playstep() {
    die();   // actually dies only if it should (alive and hp=0)
    if (get_alive()){
        //bouding energy and hp to the max bcse in case of modifications in the previous playstep
        bound_energy_hp();

        if (sleep_time) {

            sleep_step();
        }
        else if(digest_time){
            digest_step();
        }
        else {
            /* For now, create bugs due to the structure of brain
            std::vector<double> input_vector = brain.propagate(Input);
            decision(input_vector);
            */
            set_counter_no_sleep(get_counter_no_sleep()+1);  //neither eat/digest or sleep
            set_counter_no_eat(get_counter_no_eat()+1);
        }

        check_if_lack(); //lack of sleep is more damageable bcse more important to sleep than to eat, Harvard study :)

    ;}
};


void Creature::check_if_lack() {
    if (get_counter_no_eat()==24) {
        set_physical_strength(0.95*get_physical_strength());
        set_energy(0.95*get_energy());
    }
    if (get_counter_no_sleep()==24) {
        set_physical_strength(0.90*get_physical_strength());
        set_energy(0.90*get_energy());
    }
}

void Creature::sleep(double delta_t) {
    sleep_time = delta_t;
}

void Creature::sleep_step() {
    set_counter_no_sleep(0);
    set_counter_no_eat(get_counter_no_eat()+1);
    double e = get_energy() +1;
    set_energy(e);
    sleep_time-=1;
}


LivingBeing* Creature::find_food(){
    // this function is gonna return the closest dead living being (that you can eat), or no living being
    std::vector<LivingBeing*> close = get_close(); //we look at all the living beings that are close
    vector<LivingBeing*>::iterator i=close.begin();
    while(i!=close.end()){ //here we'll check if they are alive and we can eat them
        if((*i)->get_alive() == false && ((*i)->type == plant && get_eat_plants()) || ((*i)->type==creature && get_eat_creature())){
            this->set_found_food(true);
            return *i;
        }
        else{i++;}
    }
    set_found_food(false);
    return nullptr;

};



void Creature::eat(LivingBeing &l, double eat_time){
    // this function first determines the initial gains of eating, then digests: depending on the type of the lb eaten
    // initial gains depend from what you can eat, the size of the creature, and the eat_time(faster you eat, less you gain)
    //
    //
    // small modification : if l is a plant, then we already modify the attributes of *this creature in l.is_eaten(*this)
    // called in digest(l, eat_time),(the modifications to *this depend on the characteristics of the plant)
    //and we also do damage to the plant itself.
    //
    // if l is a creature then we modify the attributes of *this in eat(l,eat_time) below and we do damage to l in l.is_eaten(*this)
    //which is called in digest(l, eat_time)

    set_counter_no_eat(0);

    if (l.type == creature) {

        //modifying the eater's attributes:

        double alpha;
        if(get_eat_creature() && get_eat_plants()){alpha = 0.8;}
        else{alpha=1;}
        double gain = alpha*eat_time*l.get_size();
        double current_energy = get_energy();
        set_energy(gain + current_energy);}

    digest(l, eat_time);
    this->set_found_food(false);

}


void Creature::digest(LivingBeing &food, double eat_time){
    // when food is digested, it will also create negative "side-effects" such as increase your visibility,
    // it will also make your size sightly bigger
    // it will also make your physical strength lower for a few turns
    food_attributes.push_back(food.get_size());

    if (food.type == creature) { // a creature being eaten
        digest_time = ceil(eat_time * 10); // 10 has been chosen at random, may be arbitrarily changed later if necessary
        food.is_eaten(*this);}

    else if (food.type == plant) { // a plant being eaten
        digest_time = ceil(eat_time * 6); // 6 is arbitrary too here
        food.is_eaten(*this); //implements all that can happen when a creature eats a plant
    }

};


void Creature::digest_step(){
    set_counter_no_eat(0);
    set_counter_no_sleep(get_counter_no_sleep()+1);  //does not sleep but gets the benefits of eating
                                                    //so no need to increase counter_no_eat

    if (food_attributes.size()){
        if (digest_time == 1) {
            digest_time = 0;
            set_visibility(0.5); //arbitrary value, to be changed if needed
            set_physical_strength(0.5); //arbitrary value, to be changed if needed
        }
        else {
            digest_time -= 1;
            if (get_visibility()*1.1*food_attributes[0] <= 1) {
                set_visibility(get_visibility()*1.1*food_attributes[0]);}
            else { set_visibility(1);}}

            if (get_physical_strength()*0.95*food_attributes[0] >= 0) {
                set_physical_strength(get_physical_strength()*0.95*food_attributes[0]);
            }
            else {set_physical_strength(0);}
     }
};


//Vision is simulated using multiple rays which will start from the creature trying to see an go on multiple dircetion.
//The see function will return a vector of size 3*n containing the distance, the size and hp of the first living_being (only distance for non_living beings) that ta ray collide with.
std::vector<double> Creature::See(int n){
    std::vector<double> v; //Here we'll get all the output, It will be of size n

    for (int i=0; i<n; i++){
        std::vector<double> v2 = this->See(n, i);
        for (std::vector<double>::iterator j=v2.begin(); j!=v2.end(); j++){
            v.push_back(*j);
        }
    }
    return v;
}

//This is an auxiliar function of the See(int) function
std::vector<double> Creature::See(int n, int i){
    // return a distance score with 0 meaning really close and 256 meaning nothing seen (see only the closest object)

    //start: x, y; teta = ((i+1)*pi)/(n+2), this will allow us to get the vision ray at good positions.
    std::vector<double> v;
    double r=-1;
    double teta = ((i+1)*3.14)/(n+2) + this->rotation()*(3.14/180);


    //lenght is vision
    QGraphicsLineItem*  Ray = new QGraphicsLineItem(this->x(), this->y(), this->x() + this->get_eye_sight() * cos(teta), this->y() + this->get_eye_sight() * sin(teta));
    QList<QGraphicsItem*> list = Ray->collidingItems();

    LivingBeing* last_seen  = nullptr;
    foreach(QGraphicsItem* i , list)
    {
        double* R = new double(pow(pow(i->x(), 2) + pow(i->y(), 2), 0.5));
        if (r == -1 || *R <r){
            r = *R;
            last_seen = dynamic_cast<LivingBeing*>(i);;
        }
        delete R;
    }
    delete Ray;

    //We rescall r for easier learning:
    if (r ==-1){
        r = this->get_eye_sight()+1;
    }

    //first is the distance
    v.push_back(r);
    //we'll then try a dynamic cast to know what we add after:
    if (last_seen==nullptr){
        v.push_back(-1);
        v.push_back(-1);
        return v;
    }

    //we then add size:
    v.push_back(last_seen->get_size());
    //we then add healthpoints:
    v.push_back(last_seen->get_hp());
    return v;
}


const float _dtheta = 20; //base value of the change of rotation - to set maximal rotation range to 10 degrees
const float _ddistance = 2; //base value of the change of the distance - maximal value of move is 2
const float _ener_rotcoeff = 0.05; //base value for energy consumption while rotating
const float _ener_movecoeff = 0.5; //base value for energy consumption while moving
const float _sizecoeff = 0.1; //base value for energy punishment connected with the size;
//move function first moves the creature by the distance with respect to angle getrotation from qtgraphicsitem
//then changes the rotation (so rotation applies only for next movements)
void Creature::move(double rotation, double distance){
    setRotation(this->rotation() + rotation * _dtheta);

    setX(this->x() + (distance*_ddistance) * cos(this->rotation()*M_PI/180));
    setY(this->y() + (distance*_ddistance) * sin(this->rotation()*M_PI/180));

    float s = this->size;
    float current_energy = get_energy();
    current_energy -= (_ener_rotcoeff * rotation + _ener_movecoeff * distance) * _sizecoeff * s * s; //change of energy depends on rotation, distance travelled and size squared to punish too big animals
    set_energy(current_energy);
}

