#include <random>
#include "QtGui/qpainter.h"
#include "creature.h"
#include "Neural_Network/network.hpp"
#include "plant.h"
#include "living_being.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <QGraphicsItem>
#include "environment.h"
#include <QRandomGenerator>


int Creature::n_families = 0;

bool Show_Sight = false;
const float _dtheta = 20; //base value of the change of rotation - to set maximal rotation range to 10 degrees
const float _ddistance = 2; //base value of the change of the distance - maximal value of move is 2
const float _ener_rotcoeff = 0.2; //base value for energy consumption while rotating
const float _ener_movecoeff = 0.5; //base value for energy consumption while moving
const float _sizecoeff = 0.1; //base value for energy punishment connected with the size;


Creature::Creature(bool newfamily):LivingBeing() {

    //we need a way to differenciate animals and plants
    color = QColorConstants::DarkGray;
    // in the iteration param refers to an int into Enum_parameters (which does not include the value last)
    for (Enum_parameters param = (Enum_parameters)0 ; param != last; param=(Enum_parameters)(param+1)) {
        double val = min(200.0,abs(1+((double)QRandomGenerator::global()->generateDouble()*200))); // val is the random value that we will assign to val
        this->parameters.insert(std::pair<Enum_parameters, double>(param, val));
    };
    my_size = min(200.0,abs(1+((double)QRandomGenerator::global()->generateDouble()*200)));
    this->set_energy(this->get_Max_energy());
    this->set_hp(this->get_Max_hp());


    // the brain is already constructed by the default constructor in the .h file.
    type = creature;
    this->set_alive(true);
    found_food = false;
    counter_no_eat=0;

    //We then need to take care of preys and predators:
    if (this->parameters[eat_creature]>100){
        this->parameters[eat_creature]=1;
        i_eat_creatures = true;
        this->parameters[eat_plants]=0;
        i_eat_plants = false;
    }
    else{
        this->parameters[eat_creature]=0;
        i_eat_creatures = 0;
        this->parameters[eat_plants]=1;
        i_eat_plants = 1;

    }

    //For the input: each vision ray has 3 outputs; then we have 2 times 8 attributes taken into account (at turn t and t-dt); and then two memory variables
    Network* n = new Network(3, 1, 1, 2);
    this->brain = n;


    parameters[eye_sight] = 50;
    if(newfamily){
      this->family = Creature::n_families;
      Creature::n_families++;
      }


}


bool Creature::Check_Overlap_Creature(Environment* e){
    return (false);
    QList<QGraphicsItem*> list = e->collidingItems(this);
    return (!list.isEmpty());
}


Creature::Creature(Environment* e): Creature(){
    this->set_scene(e);
    if (Check_Overlap_Creature(e)){
        set_alive(false);
    }
}



Creature::Creature(std::map<Enum_parameters, double> parameters, Network *brain, Environment* e): Creature(e) {

    this->parameters = parameters;
    this->base_parameters = parameters; //we save "dna"
    this->brain = brain;
    //To be sure there are no excess:
    if (this->get_size()>200){
        this->set_size(200);
    }
    else if (this->get_size()<5){
        this->set_size(5);
    }

    parameters[eye_sight] = 50;


}

Creature::~Creature() {

    this->scene->removeItem(this);
    if (get_eat_creature()){
        this->scene->predators_nb -=1 ;
    }
    else {
        std::cout << "hey" << std::endl;
        this->scene->preys_nb -= 1;
    }
  //delete this->brain;
}

QPainterPath Creature::shape() const
{
    double K = this->get_size()/1000; //size coefficient
    QPainterPath path;
    if(!get_eat_creature()){
        path.addRect(-15*K, -22*K, 30*K, 60*K);
    }
    else {
        path.addRect(-12*K, -12*K, 24*K, 24*K);
    }
    return path;

}

void Creature::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (Show_Sight){
        painter->drawEllipse(-this->get_eye_sight()/2, -this->get_eye_sight()/2, this->get_eye_sight(), this->get_eye_sight());
    }

    double K = this->get_size()/600; //size coefficient
    QColor bodycolor = QColor((10001 * family % 256), (1001 * family % 256), (100001 * family % 256), 255);
    if(!get_eat_creature()){
        // Body
        painter->setBrush(bodycolor); //for now make it redder the more energy it can have
        painter->drawEllipse(-10*K, -20*K, 20*K, 40*K);

    } else {
        painter->setBrush(bodycolor);
        painter->drawEllipse(QRectF(-12*K,-12*K,24*K,24*K));
    }

    LivingBeing::paint(painter, option, widget);
}

Creature* Creature::reproduction() {
    std::map<Enum_parameters, double> param_new_creature;
    for ( Enum_parameters param = (Enum_parameters)0; param != last; param=(Enum_parameters)(param+1) ) {
        double val = max(0.0,min(200.0,normal_distrib(parameters[param], 10))); // 0.1 is arbitrary value
        param_new_creature.insert(std::pair<Enum_parameters, double>(param, val));
    }

    //Creature can change from prey to predators, and the reverse
    param_new_creature[eat_creature]=parameters[eat_creature];
    param_new_creature[eat_plants]=parameters[eat_plants];


    //Copy of current brain
    Network* new_brain = brain->copy();



    //Network new_brain = network(old brain);
    // modify this function when we can create new networks with inputs
    new_brain->apply_on_all_weights(normal_distrib_random());
    Creature* C= new Creature(param_new_creature, new_brain, this->get_scene());
    C->i_eat_creatures = this->i_eat_creatures;
    C->i_eat_plants = this->i_eat_plants;
    C->my_size = max(0.0,min(200.0,normal_distrib(this->my_size, 10)));;
    C->set_scene(this->get_scene());
    C->setPos(x(), y());
    C->setRotation(rotation());
    C->move(10, 10); //So that they aren't both exactly at the same place, and wont stay at the same position and do the same things

    C->set_family(this->get_family());
    return C;
};


void Creature::take_dmg(double dmg){
    set_last_attack(0);
    if (this->get_hp()>0){
        this->set_hp(this->get_hp()-dmg);
    }
    die();
}


std::vector<LivingBeing*> Creature::get_close(){
    std::vector<LivingBeing*> v; //creates a vector that will store the beings near you
    QRectF bounding_rect(this->x() -  size/2 , this->y() - size/2, size, size); //creates a bounding rect around the creature
    QList<QGraphicsItem*> close = this->get_scene()->items(bounding_rect); //creates list close of colliding items


    for (QGraphicsItem* item : close){
        LivingBeing *L = dynamic_cast<LivingBeing*>(item);
        // if item was possible to cast && if they don't have the same coordinates
        if (L!=nullptr){
            v.push_back(L);
        }
    }
    return v;
}





void Creature::die() {
    if (get_counter_no_eat()>250 || (!this->get_alive()) || (this->get_hp() < 0) ) {
        set_alive(false);
        //Creature::~Creature();
    }

};



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
bool Creature::get_eat_creature() const{return this->i_eat_creatures;}
bool Creature::get_eat_plants() const{return this->i_eat_plants;}
int Creature::get_digest_time(){return this->digest_time;}
void Creature::set_digest_time(int time){this->digest_time = time;}
std::vector<double> Creature::get_food_attributes() {return this->food_attributes;}
 //void Creature::set_food(LivingBeing &f){this->food = f;}
void Creature::set_size(double s){this->my_size = s;}
double Creature::get_size() const{return this->my_size;}
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
Network* Creature::get_brain(){return brain;};
void Creature::set_brain(Network* b){brain = b;};
int Creature::get_last_attack(){return this->last_attack;};
void Creature::set_last_attack(int i){this->last_attack = i;};
double Creature::get_parameter(Enum_parameters p){return this->parameters.at(p);};
void Creature::set_family(int f){this->family = f;};
int Creature::get_family(){return this->family;};

void Creature::bound_energy_hp() {
    if (get_energy()>get_Max_energy()) {
        set_energy(get_Max_energy());}
    if (get_hp()>get_Max_hp()) {
        set_hp(get_Max_hp());}
}

std::function<double(double)> Creature::normal_distrib_random(){ return [](double weight){
    //takes an weight of an edge and has a 10% percent chance to modify the weight according to the normal distribuition.
    std::random_device rd;
    std::mt19937 gen(rd());
    std:exponential_distribution<double> e(4);

    double p_cut_off = e(gen);
    double p =QRandomGenerator::global()->generateDouble();
    if (p < p_cut_off){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> d(weight, 10);
        weight = d(gen);
    }
    return weight;
};}


//input_vector : (rotation, distance)

void Creature::decision(std::vector<double> input_vector,LivingBeing* c){

        double towards = input_vector[0];
        if(towards > 0.5){
            move_to(c,_ddistance);
          } else {
            move_to(c, -_ddistance);
          }
}


//This is what we'll b e using to eat whatever the LB is touching and can eat
void Creature::Eat(){
    QList<QGraphicsItem*> list = get_scene()->collidingItems(this);

    if (get_eat_creature() && repro_factor>=20){
        repro_factor -= 20;
        if (get_eat_creature()){
            if (this->scene->predators_nb < this->scene->max_predators_nb){
                Creature* c = reproduction();
                this->scene->addItem(c);
                this->scene->predators_nb += 1;
            }
        }
        else {
            if (this->scene->preys_nb < this->scene->max_preys_nb){
                Creature* c = reproduction();
                this->scene->addItem(c);
                this->scene->preys_nb += 1;
            }
        }
    }
    else if (repro_factor>=60){
        repro_factor -= 60;
        if (get_eat_creature()){
            if (this->scene->predators_nb < this->scene->max_predators_nb){
                Creature* c = reproduction();
                this->scene->addItem(c);
                this->scene->predators_nb += 1;
            }
        }
        else{
            if (this->scene->preys_nb < this->scene->max_preys_nb){
                Creature* c = reproduction();
                this->scene->addItem(c);
                this->scene->preys_nb += 1;
            }
        }
    }



    foreach(QGraphicsItem* i , list){

        Plant *j = dynamic_cast<Plant*>(i);
        Creature *k = dynamic_cast<Creature*>(i);
        bool ate = false;
        if (j != nullptr && this->get_eat_plants()){
          ate = true;
          j->set_alive(false);
          j->die();
        }
        if ( k != nullptr && this->get_eat_creature()){

            if(k->get_eat_creature()){
                if( k->family == this->family){
                   return;
                  }
                if (k->get_size() <= this->get_size()){
                    ate = true;
                    k->set_alive(false);
                    k->die();
                } else {
                    this->set_alive(false);
                    //k->set_energy(get_Max_energy());
                    k->repro_factor += 20;
                    k->set_counter_no_eat(0);
                    die();
                  }
              } else {
                double r = (double) QRandomGenerator::global()->generateDouble();
                r*=4;//Creature can at most eat something 4 times bigger
                if (r>(k->get_size())/(get_size())){
                    ate = true;
                    k->set_alive(false);
                    k->die();
                }
              }
        }
        if(ate ){
          //set_energy(get_Max_energy());
          repro_factor+=20;
          set_counter_no_eat(0);
          }
    }


}


void Creature::playstep() {

    //PACMAN, when touching a border, the creature is TPed on the other side, however this is not exactly how the border of pacman works... (is is continuous)
    if (this->x()<0){
        setX(500+x());
        setY(500-y());
    }
    if (this->y()<0){
        setX(500-x());
        setY(500+y());
    }
    if (this->x()>500){
        setX(500-x());
        setY(500-y());
    }
    if (this->y()>500){
        setX(500-x());
        setY(500-y());

    }



    increase_alive_time();
    die();   // actually dies only if it should (alive and hp<=0)


    if (get_alive()){

        //bouding energy and hp to the max bcse in case of modifications in the previous playstep
        bound_energy_hp();
        LivingBeing*  closest_being = std::get<LivingBeing*>(get_closest(1)[0]);

        std::vector<double> Input =get_params(closest_being);

        //std::cout<<"input vector:  ";
        //Other::Cout_Vector(Input);
        std::vector<double> decision_vector = brain->propagate(Input);

        decision(decision_vector, closest_being);
        set_counter_no_eat(get_counter_no_eat()+1);
        Eat();


    ;} else {
        Creature::~Creature();
      }
};

vector<double> Creature::get_params(LivingBeing* l){
  if (l== nullptr){
      return {-1,-1,-1};
    }
  vector<double> v;
  v.push_back(l->get_size());
  int l_t = l->get_type();
  int my_t = this->get_type();
  int can_eat_me = 0;
  int can_eat_it = 0;
  if(l_t == 2){
      //if l_t is creature
      Creature* c = dynamic_cast<Creature*>(l);
      can_eat_me = (int) c->get_eat_creature();
      can_eat_it = (int) this->get_eat_creature();
    } else {
      can_eat_it = (int) this->get_eat_plants();
    }
  v.push_back(can_eat_me);
  v.push_back(can_eat_it);
  return v;
}


double distance(double ax, double ay, double bx, double by){
  return (double) sqrt((ax-bx)*(ax-bx) + (ay-by)*(ay-by));
}
double distance(LivingBeing* a, LivingBeing* b){
  float ax = a->x();
  float ay = a->y();
  float bx = b->x();
  float by = b->y();
  return distance(ax,ay,bx,by);
}


void Creature::move_to(LivingBeing* other, double d){

  if(dynamic_cast<Plant*>(other) != nullptr){
      //std::cout<<"I move to a plant!" << std::endl;
    }
  double x = this->x(); double y = this->y();
  double ox; double oy;
  if(other == nullptr){
      ox = 1000*QRandomGenerator::global()->generateDouble();
      oy = 1000*QRandomGenerator::global()->generateDouble();
    } else {
     ox = other->x(); oy = other->y();
    }
  double r = distance(x,y,ox,oy);
  setX(x + (d/r)*(ox-x) );
  setY(y + (d/r)*(oy-y) );
  float s = this->size;
  float current_energy = get_energy();
  current_energy -= _ener_movecoeff * abs(d) * _sizecoeff * s * s; //change of energy depends on rotation, distance travelled and size squared to punish too big animals
  set_energy(current_energy);
}

std::vector<std::tuple<double,LivingBeing*>> Creature::get_closest(int n){
  std::vector<std::tuple<double,LivingBeing*>> info_vec;
  double w = 1000; double h = 1000;
  QRectF bounding_rect(this->x() -  w/2, this->y() - h/2, w, h); //creates a bounding rect around the creature
  QList<QGraphicsItem*> close = this->get_scene()->items(bounding_rect); //creates list close of colliding items

  std::vector<double> distances;

  for (QGraphicsItem* item : close){
      LivingBeing *L = dynamic_cast<LivingBeing*>(item);
      // if item was possible to cast && if they don't have the same coordinates
      if (L!=nullptr && L->family != this->family){
          double d = distance(this,L);
          if(d > 0.001){
            distances.push_back(d);
            info_vec.push_back(std::make_tuple(d,L));
          }
      }
  }
  std::vector<std::tuple<double,LivingBeing*>> return_vector;
  if(distances.size() <= n){
      for (int i = 0; i < distances.size(); i++) {
           return_vector.push_back(info_vec[i]);

        }
    } else {
      std::sort(distances.begin(),distances.end());
      double cutoff = distances[n-1];
      for (auto l: info_vec) {
          if(return_vector.size() == n){
              return return_vector;
            }
          if(std::get<double>(l) <= cutoff){
              return_vector.push_back(l);
            }
        }
    }
  while(return_vector.size()<n){
      return_vector.push_back(std::make_tuple(-1,nullptr));
    }
  return return_vector;

}

//Vision is simulated using multiple rays which will start from the creature trying to see an go on multiple direction.
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

    std::vector<double> v;
    double r=-1;
    double teta = ((i)*2*3.14)/(n) + this->rotation()*(3.14/180);


    //lenght is vision
    QGraphicsLineItem*  Ray = new QGraphicsLineItem(0, 0, this->get_eye_sight() * cos(teta), this->get_eye_sight() * sin(teta));

    QList<QGraphicsItem*> list = get_scene()->collidingItems(Ray);

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


    //we then add type:
    Plant* j = dynamic_cast<Plant*>(last_seen);
    if (j!= nullptr){
        v.push_back(1);
    }
    else{
        Creature* j = dynamic_cast<Creature*>(last_seen);
        if (j!= nullptr){
            v.push_back(2);
        }
        else{
            v.push_back(3);
        }
    }

    return v;
}



//move function first moves the creature by the distance with respect to angle getrotation from qtgraphicsitem
//then changes the rotation (so rotation applies only for next movements)
void Creature::move(double rotation, double distance){
    setRotation(this->rotation() + rotation * _dtheta);
    float w = get_scene()->width();
    float h = get_scene()->height();

    setX(fmod(this->x() + (distance*_ddistance) * cos(this->rotation()*M_PI/180 - M_PI/2),w));
    setY(fmod(this->y() + (distance*_ddistance) * sin(this->rotation()*M_PI/180 - M_PI/2),h));

    float s = this->size;
    float current_energy = get_energy();
    current_energy -= (_ener_rotcoeff * rotation + _ener_movecoeff * distance) * _sizecoeff * s * s; //change of energy depends on rotation, distance travelled and size squared to punish too big animals
    set_energy(current_energy);
}


QRectF Creature::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF((-18 - adjust)*get_size()/200, (-22 - adjust)*get_size()/200,
                  (36 + adjust)*get_size()/200, (60 + adjust)*get_size()/200);
}

