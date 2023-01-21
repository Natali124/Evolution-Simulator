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
#include <QGraphicsColorizeEffect>
#include <QRandomGenerator>
//using namespace std;

const int repro_cost_predator = 40;// cost of reproduction of predators (20 = 1x food)
const int repro_cost_prey = 20; // cost of reproduction of predators (20 = 1x food)
const int food_value_plant = 20; // value of a plant to be added to repro_factor upon consumption
const int food_value_animal = 40; // value of a creature to be added to repro_factor upon consumption
const double seeing_rect = 500; // size of rectangle in which creatures see
const int repro_cool_down = 50; // how many steps between reproductions
const double _predator_speed_bonus = 0; // gives predators more / less speed
const float _ddistance = 2; //base value of the change of the distance
const double starving_rate = 0.2; // rate of starving, 0 = no starving, 1 = starving very quickly
const int repro_factor_decrease = 4; // decrease of repro_factor per step


const bool allow_cannibalism = false; // allow creatures of same family to eat each other?
const bool can_see_own_family = false; // can creatures see their own family?
const bool preds_can_see_plants = false; // can predators see plants?
const bool kill_overlapping = false; // kill overlapping preys?

const int _n_closest_visible = 2; //number of closest visible beings
const int n_input = 4*_n_closest_visible; //size of input vector to neural network
const int n_output = _n_closest_visible; // size of output vector of neural network

int Creature::n_families = 0;

// not used right now
bool Show_Sight = false;
const float _dtheta = 20; //base value of the change of rotation - to set maximal rotation range to 10 degrees
const float _ener_rotcoeff = 0.2; //base value for energy consumption while rotating
const float _ener_movecoeff = 0.5; //base value for energy consumption while moving
const float _sizecoeff = 0.1; //base value for energy punishment connected with the size;


void Creature::stay_in_bounds(){
  //PACMAN, when touching a border, the creature is Teleported to the other side
  if (this->x()<0){
      setX(-x());
      setY(y());
  }
  if (this->y()<0){
      setX(x());
      setY(-y());
  }
  if (this->x()>500){
      setX(1000-x());
      setY(y());
  }
  if (this->y()>500){
      setX(x());
      setY(1000-y());

  }
}


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
    Network* n = new Network(n_input,n_output, 1, n_input);
    this->brain = n;


    parameters[eye_sight] = 50;
    effect = new QGraphicsColorizeEffect;
    QColor bodycolor = QColor((10001 * family % 256), (1001 * family % 256), (100001 * family % 256), 255);
    if(newfamily){
      this->family = Creature::n_families;
      Creature::n_families++; 
      effect->setColor(QColor((10001 * family % 256), (1001 * family % 256), (100001 * family % 256), 255));
      this->setGraphicsEffect(effect);
      }
    else{
        effect->setColor(Qt::transparent);
        this->setGraphicsEffect(effect);
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
    effect = new QGraphicsColorizeEffect;
    effect->setColor(QColor((10001 * family % 256), (1001 * family % 256), (100001 * family % 256), 255));
    this->setGraphicsEffect(effect);
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

    double K = this->get_size()/1000; //size coefficient
    if(!get_eat_creature()){

        if(family%2==1){
            painter->drawImage(boundingRect().toRect(),deer);
        }
        else{
            painter->drawImage(boundingRect().toRect(),gazelle);
        }

    } else {
        if(family%2==1){
            painter->drawImage(boundingRect().toRect(),wolf);
        }
        else{
            painter->drawImage(boundingRect().toRect(),lion);
        }


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

    // Reproduce current brain
    Network* new_brain = brain->reproduce();

    Creature* C= new Creature(param_new_creature, new_brain, this->get_scene());
    C->i_eat_creatures = this->i_eat_creatures;
    C->i_eat_plants = this->i_eat_plants;
    C->my_size = max(0.0,min(200.0,normal_distrib(this->my_size, 10)));;
    C->set_scene(this->get_scene());
    C->setPos(x() + 10, y() + 10);
    C->setRotation(rotation());

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
    bool starved = false; // see if starved to death (random)

    // probability of starving after not eating for s steps, follows sigmoid function
    double x = ((get_counter_no_eat()*starving_rate/20) -10);
    x = 1/(pow(M_E, -x) + 1);
    double p = QRandomGenerator::global()->generateDouble();
    if(p < x){
        starved = true;
      }

    if (starved|| (!this->get_alive()) || (this->get_hp() < 0) ) {
        // actually die
        set_alive(false);
    }};



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

void Creature::set_family(int f){
    effect = new QGraphicsColorizeEffect;
    effect->setColor(QColor((10001 * f % 256), (1001 * f % 256), (100001 * f % 256), 255));
    this->setGraphicsEffect(effect);
    this->family = f;};
int Creature::get_family(){return this->family;};

void Creature::bound_energy_hp() {
    if (get_energy()>get_Max_energy()) {
        set_energy(get_Max_energy());}
    if (get_hp()>get_Max_hp()) {
        set_hp(get_Max_hp());}
}

void Creature::try_reproduce(){
    // reproduces if possible

    if(counter_no_reproduction <repro_cool_down){
        // if still in cooldown, return
        return;}
    // check if can reproduce
    bool reproduce = false;
    if (get_eat_creature() && repro_factor>=repro_cost_predator){
          repro_factor -= repro_cost_predator;
          reproduce = true;
      }
     else if (repro_factor>=repro_cost_prey){
          repro_factor -= repro_cost_prey;
          reproduce = true;
      }


    // actually reproduce, if possible
    if(reproduce){
        Creature* c = this->reproduction();
        this->get_scene()->addItem(c);
        counter_no_reproduction = 0;
      }
}


void Creature::decision(std::vector<double> input_vector,vector<LivingBeing*> c){
        // takes action based on decision vector
        double towards = -1; // saves most "extrem" decision toward ( =1) or away (=0) from something
        double index = 0; // save index of being we want to move towards / away from
        for (int i = 0; i < input_vector.size(); i++) {
            double magnitude = input_vector[i];
            if(towards == -1 or abs(magnitude -0.5)>abs(towards-0.5)){
                // if magnitude at this index is farther away from 0.5, this is our new target
                index = i;
                towards = magnitude;
              }
          }
        LivingBeing* target = c[index]; // target to move towards / away from

        double x = 3.25-2.5/(pow(M_E, -double(this->get_size())/40) + 1);
        double speed = _ddistance *(1 + _predator_speed_bonus* (int)(i_eat_creatures))*x; // speed is inversely correlated to size
        if(towards > 0.5){
            // move towards target
            move_to(target,speed);
          } else {
            // move away from target
            move_to(target,-speed);
          }

}

void Creature::Eat(){
    // Determines what happens when creatures collide
    QList<QGraphicsItem*> list = get_scene()->collidingItems(this);

    foreach(QGraphicsItem* i , list){
        Plant *j = dynamic_cast<Plant*>(i);
        Creature *k = dynamic_cast<Creature*>(i);
        bool ate = false;
        if (j != nullptr && this->get_eat_plants()){
            // j is plant and this can eat plants
            ate = true;
            repro_factor += food_value_plant;
            j->set_alive(false);
            j->die();
        }
        if ( k != nullptr && this->get_eat_creature()){
            // if this is a predator and k is a creature

            if(k->get_eat_creature()){ // if creature k is a predator
                if( !allow_cannibalism && k->family == this->family){
                    // if same family, nothing happens (no cannibalism)
                   return;
                  }
                double r = (double) QRandomGenerator::global()->generateDouble(); //random variable to decide who wins fight
                double p = (double) QRandomGenerator::global()->generateDouble();
                if (r*this->get_size() > p*k->get_size() ){
                    // this wins and eats k
                    ate = true;
                    repro_factor += food_value_animal;
                    k->set_alive(false);
                    k->die();
                } else {
                    // creature k wins and eats this
                    this->set_alive(false);
                    k->repro_factor += food_value_animal;
                    k->set_counter_no_eat(0);
                    die();
                  }
              } else { // creature k is a prey
                double r = (double) QRandomGenerator::global()->generateDouble(); //random variable to decide who wins fight
                double size_quotient = (k->get_size())/(get_size());
                //Creature can at most eat something 4 times bigger
                if (4*r>size_quotient){
                    // this wins and eats k
                    ate = true;
                    repro_factor += food_value_animal;
                    k->set_alive(false);
                    k->die();
                }
              }
        } else if(k != nullptr && kill_overlapping){
            // if this is a herbivore and k is a creature
            double r = (double) QRandomGenerator::global()->generateDouble(); //random variable to decide who wins fight
            double p = (double) QRandomGenerator::global()->generateDouble();

            if(r * this->get_size() > p*k->get_size()){
                this->set_alive(false);
                this->die();
              } else {
                k->set_alive(false);
                k->die();
              }
          }
        if(ate ){
          set_counter_no_eat(0);
          }
    }


}


void Creature::playstep() {
    this->stay_in_bounds(); // make sure we stay in borders

    die();   // actually dies only if it should (alive and hp<=0)

    if (get_alive()){
        try_reproduce(); // reproduce if possible

        //bouding energy and hp to the max bcse in case of modifications in the previous playstep
        bound_energy_hp();

        // get closest being (for now only very closest one)
        std::vector<std::tuple<double,LivingBeing*>> closest = get_closest(_n_closest_visible);
        vector<LivingBeing*> closest_beings;
        vector<double> input_vector;
        for (auto t : closest) {
            LivingBeing* being = std::get<LivingBeing*>(t);
            for (double param : get_params(being)) {
                input_vector.push_back(param);
              }
            //input_vector.push_back(std::get<double>(t));
            closest_beings.push_back(std::get<LivingBeing*>(t));
          }




        // get decision_vector from brain
        std::vector<double> decision_vector = brain->propagate(input_vector);

        counter_no_reproduction++;
        repro_factor = max(0.0, repro_factor-repro_factor_decrease); // lose some reproduction factor
        decision(decision_vector, closest_beings); // take decision with regards to closest being
        set_counter_no_eat(get_counter_no_eat()+1);
        Eat(); // if colliding with something, eat or die
    ;} else {
        delete this; // deletes itself if dead
      }
};

vector<double> Creature::get_params(LivingBeing* l){
  // turn Living being into paramter for neural network
  // (size coefficient [1/200,200], can_eat_me {0,1}, can_eat_it {0,1}, same_family {0,1})
  if (l== nullptr){
      // if no living being, fill vector with -1
      return {-1,-1,-1,-1};
    }
  vector<double> v; // vector to store parameters

  v.push_back(l->get_size()/this->get_size()); // quotient of sizes (<1 -> this creature is bigger than l)

  int can_eat_me = 0; // 1 if l can eat this
  int can_eat_it = 0; // 1 if this can eat l
  Creature* c = dynamic_cast<Creature*>(l);
  if(c!= nullptr){
      //if l_t is creature
      can_eat_me = (int) c->get_eat_creature();
      can_eat_it = (int) this->get_eat_creature();
    } else {
      can_eat_it = (int) this->get_eat_plants();
    }

  // add the parameters
  v.push_back(can_eat_me);
  v.push_back(can_eat_it);

  v.push_back((int) (l->get_family() == this->family)); // 1 if same family -> always 0 right now, as blind to own family members
  return v;
}


double distance(double ax, double ay, double bx, double by){
  // distance between points (ax, ay) and (bx,by)
  return (double) sqrt((ax-bx)*(ax-bx) + (ay-by)*(ay-by));
}
double distance(LivingBeing* a, LivingBeing* b){
  // distance between Living beings a and b
  float ax = a->x();
  float ay = a->y();
  float bx = b->x();
  float by = b->y();
  return distance(ax,ay,bx,by);
}


void Creature::move_to(LivingBeing* other, double d){
  // move the distance d towards the living being "other"
  double x = this->x(); double y = this->y();
  double ox; double oy;
  if(other == nullptr ){
      // if no target is given, move randomly

      ox = 1000*QRandomGenerator::global()->generateDouble();
      oy = 1000*QRandomGenerator::global()->generateDouble();
    } else {
      ox = other->x();
      oy = other->y();
    }
  double r = distance(x,y,ox,oy);
  setX(x + (d/r)*(ox-x) );
  setY(y + (d/r)*(oy-y) );
  this->stay_in_bounds();
}

std::vector<std::tuple<double,LivingBeing*>> Creature::get_closest(int n){
  // returns the n closest living being seen (predators don't see plants, everyone is blind to their own family)
  std::vector<std::tuple<double,LivingBeing*>> info_vec;
  double w = seeing_rect; double h = seeing_rect;
  QRectF bounding_rect(this->x() -  w/2, this->y() - h/2, w, h); //creates a bounding rect around the creature
  QList<QGraphicsItem*> close = this->get_scene()->items(bounding_rect); //creates list close of colliding items

  std::vector<double> distances;

  for (QGraphicsItem* item : close){
      LivingBeing *L = dynamic_cast<LivingBeing*>(item);
      // if item was possible to cast && if they don't have the same coordinates

      if (L!=nullptr) {
          bool family_ignore = !can_see_own_family && L->get_family() == family; // check if it's the same family to be ignored
          bool plant_ignore = !preds_can_see_plants && i_eat_creatures && L->get_type() == plant; // check if it is a plant to be ignored
          bool ignore = family_ignore || plant_ignore; // if one of the two ignore cases is achieved, ignore object
          if(!ignore){ // predators don't see plants
            double d = distance(this,L);
            if(d > 0.001){
              distances.push_back(d);
              info_vec.push_back(std::make_tuple(d,L));
            }
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

QRectF Creature::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF((-18 - adjust)*get_size()/200, (-22 - adjust)*get_size()/200,
                  (36 + adjust)*get_size()/200, (60 + adjust)*get_size()/200);
}

