#include <random>
#include "creature.h"
#include "Living_Beings/living_being.h"
#include "Neural_Network/network.hpp"

#include <cmath>
#include <iostream>
#include <vector>
#include <map>

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




Creature::Creature() {
    std::map<Enum_parameters, float> parameters;
    // in the iteration param refers to an int into Enum_parameters (which does not include the value last)
    for (Enum_parameters param = (Enum_parameters)0 ; param != last; param=(Enum_parameters)(param+1)) {
        float val = (float)rand()/(float)(RAND_MAX); // val is the random value that we will assign to val
        parameters.insert(std::pair<Enum_parameters, float>(param, val));
    };
    // the brain is already constructed by the default constructor in the .h file.
    type = creature;
}

Creature::Creature(std::map<Enum_parameters, float> parameters, Network brain) {
    this->parameters = parameters;
    this->base_parameters = parameters; //we save "dna"
    this->brain = brain;

    this->set_energy(this->get_Max_energy());
    this->set_hp(this->get_Max_hp());
    type = creature;

}

void Creature::reproduction() {};


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

void Creature::take_dmg(float dmg){
    this->set_hp(this->get_hp()-dmg);
}

void Creature::attack(){
    //we'll first split between creatures and plants:
    std::vector<LivingBeing*> Close = this->get_close();

    //we can introduce vectors with creatures and plants
    std::vector<LivingBeing*> Creatures;
    std::vector<LivingBeing*> Plants; //when it comes to type of those two vectors
    //for now they will be liv beings, not creatures and plants
    for(vector<LivingBeing*>::iterator i = Close.begin(); i != Close.end(); i++){
        if(dynamic_cast<Creature*>(*i) != nullptr){
            Creatures.push_back(*i);
        }
//        if(dynamic_cast<Plants*>(*i) != nullptr){
//            Creatures.push_back(*i);
//        }
        //for now I'm going to leave it as plants are not included in a file
    }

}

void Creature::die() {if (get_alive() && this->get_hp() == 0 ) {
        set_alive(false);}
                     };

void::Creature::is_eaten(Creature &c) {
    if (get_alive() == false) {
        float alpha;
        if(c.get_eat_creature() && c.get_eat_plants()){alpha = 0.8;}
        else{alpha=1;}
        float loss = alpha*c.get_size();
        float current_energy = get_energy();
        set_energy(current_energy - loss);
    };
};


void Creature::set_energy(float e){this->energy = e;}
float Creature::get_energy(){return this->energy;}
void Creature::set_physical_strength(float ps){this->parameters[physical_strength] = ps;}
float Creature::get_physical_strength(){return this->parameters[physical_strength];}
void Creature::set_eye_sight(float es){this->parameters[eye_sight] = es;}
float Creature::get_eye_sight(){return  this->parameters[eye_sight];}
void Creature::set_visibility(float v){this->parameters[visibility] = v;}
float Creature::get_visibility(){return this->parameters[visibility];}
void Creature::set_Max_energy(float me){this->parameters[Max_energy] = me;}
float Creature::get_Max_energy(){return this->parameters[Max_energy];}
bool Creature::get_eat_creature(){return this->parameters[eat_creature];}
bool Creature::get_eat_plants(){return this->parameters[eat_plants];}
int Creature::get_digest_time(){return this->digest_time;}
void Creature::set_digest_time(int time){this->digest_time = time;}
vector<float> Creature::get_food_attributes() {return this->food_attributes;}
 //void Creature::set_food(LivingBeing &f){this->food = f;}
void Creature::set_size(float s){this->parameters[size] = s;}
float Creature::get_size(){return this->parameters[size];}
void Creature::set_hp(float s){this->hp = s;}
float Creature::get_hp(){return this->hp;}
void Creature::set_Max_hp(float mh){this->parameters[Max_hp] = mh;}
float Creature::get_Max_hp(){return this->parameters[Max_hp];}



/*
Creature::Creature() {physical_strength=0;energy=0;eye_sight=0;visibility=0;brain = Network();}
Creature::Creature(float physical_strength,float energy, float eye_sight, float visibility, Network brain) {
this-> physical_strength = physical_strength,
this-> energy=energy,this->eye_sight= eye_sight,this-> visibility=visibility,this-> brain=brain; };
*/

//input_vector : (sleep, eat, attack, move, sleep_time, eat_time, move_rotate, move_distance)
void Creature::decision(vector<float>input_vector){
    float action = *max_element(input_vector.begin(), input_vector.begin()+4);
    int j = 0;
    for (vector<float>::iterator i=input_vector.begin(); i!=input_vector.begin()+4; i++){
        if (action==*i) {break;}
        j++;
        }
    if(j){
        sleep(*(input_vector.begin()+4)); //sleep for sleep_time
    }
    if(j==1){
        LivingBeing& food = find_food();
        eat(food, *(input_vector.begin()+5));
    }

}


void Creature::playstep() {
    die();   // actually dies only if it should (alive and hp=0)
    if (get_alive()){

    if (sleep_time) {
        sleep_step();
    }
    else if(digest_time){
        digest_step();
    }
    else {
        decision(input_vector);       
    }
    ;}
};

void Creature::sleep(float delta_t) {
    sleep_time = delta_t;
}

void Creature::sleep_step() {
    float e = get_energy() +1;
    set_energy(e);
    sleep_time-=1;
}


LivingBeing& Creature::find_food(){
    // this function is gonna return the closest dead living being (that you can eat), or no living being

    // use ruben's get_close that returns a list of the living beings in front of you
    // for each living, check if dead and if edible
};

void Creature::eat(LivingBeing &l, float eat_time){
    // what do you gain when eating?
    //--> gonna depend from what you can eat, (if you eat only animals or plants, set an alpha = 1, if you eat both, set alpha=0.8)
    //-->from the size of the creature l.size
    //--> and depends from the speed eatime (between 0 and 1 --> the faster you eat, the less you gain)
    // so total gain is alpha*l.size*eattime
    float alpha;
    if(get_eat_creature() && get_eat_plants()){alpha = 0.8;}
    else{alpha=1;}
    float gain = alpha*eat_time*l.get_size();
    float current_energy = get_energy();
    set_energy(gain + current_energy);
    digest(l, eat_time);

}


void Creature::digest(LivingBeing &food, float eat_time){
    // when food is digested, it will also create negative "side-effects" such as increase your visibility,
    // it will also make your size sightly bigger
    // it will also make your physical strength lower for a few turns
    food_attributes.push_back(food.get_size());

    if (food.type == 0 || food.type == 1) { // a creature being eaten
        digest_time = ceil(eat_time * 10);} // 10 has been chosen at random, may be arbitrarily changed later if necessary

    else if (food.type == 2) { // a plant being eaten
        digest_time = ceil(eat_time * 6); // 6 is arbitrary too here
        food.is_eaten(*this); //implements all that can happen when a creature eats a plant
    }

};
void Creature::digest_step(){
    if (digest_time == 1) {
    }
    else {
        digest_time -= 1;
        if (get_visibility()*1.1*food_attributes[0] <= 1) {
            set_visibility(get_visibility()*1.1*food_attributes[0]);}
        else { set_visibility(1);}}

        if (get_physical_strength()*0.95*food_attributes[0] <= 1) {
            set_visibility(get_physical_strength()*0.95*food_attributes[0]);
        }
        else {set_physical_strength(1);}
};


std::vector<int> Creature::See(int n){
    std::vector<int> v; //Here we'll get all the output, It will be of size n

    for (int i=0; i<n; i++){
        v.push_back(this->See(n, i));
    }
    return v;
}

int Creature::See(int n, int i){
    // return a distance score with 0 meaning really close and 256 meaning nothing seen (see only the closest object)

    //start: x, y; teta = ((i+1)*pi)/(n+2), this will allow us to get the vision ray at good positions.
    int r=0;
    double teta = ((i+1)*3.14)/(n+2);


    //lenght is vision
    QGraphicsLineItem*  Ray = new QGraphicsLineItem(this->get_x(), this->get_y(), this->get_x() + this->get_eye_sight() * cos(teta), this->get_y() + this->get_eye_sight() * cos(teta));
    QList<QGraphicsItem*> list = Ray->collidingItems();

    foreach(QGraphicsItem* i , list)
    {
        int* R = new int(pow(pow(i->x(), 2) + pow(i->y(), 2), 0.5));
        if (*R <r){
            r = *R;
        }
        delete R;
    }
    delete Ray;

    return 1-r;
}


const float _dtheta = M_PI/18; //base value of the change of rotation - to set maximal rotation range to 10 degrees
const float _ddistance = 2; //base value of the change of the distance - maximal value of move is 2
const float _ener_rotcoeff = 0.05; //base value for energy consumption while rotating
const float _ener_movecoeff = 0.5; //base value for energy consumption while moving
const float _sizecoeff = 0.1; //base value for energy punishment connected with the size;
//move function first moves the creature by the distance with respect to angle getrotation from qtgraphicsitem
//then changes the rotation (so rotation applies only for next movements)
void Creature::move(float rotation, float distance){
    setX(distance * cos(this->rotation() * _dtheta));
    setY(distance * sin(this->rotation() * _dtheta));
    setRotation(this->rotation() + rotation);
    float s = this->size;
    float current_energy = get_energy();
    current_energy -= (_ener_rotcoeff * rotation + _ener_movecoeff * distance) * _sizecoeff * s * s; //change of energy depends on rotation, distance travelled and size squared to punish too big animals
    set_energy(current_energy);
}

