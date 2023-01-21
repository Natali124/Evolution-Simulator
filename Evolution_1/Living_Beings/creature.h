#ifndef CREATURE_H
#define CREATURE_H
#include "living_being.h"
#include "environment.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <QGraphicsColorizeEffect>


//This namespace will be used in order to have some more object to use:
namespace Other {
    //This is a debugging tool to show vectors, only works if T is a type compatible with std::cout
    template <typename T> void Cout_Vector(std::vector<T> v){
        for (typename std::vector<T>::iterator i = v.begin(); i<v.end(); i++){
            std::cout<<*i<<" ";
        }
        std::cout<<std::endl;
    }


    // This function is returning an array of T2 that are casted from a list of type T1 from which we don't take elements that can't be casted
    // I though I would need it but it seems that not... I'll erase if I really don need it, Ruben
    template <typename T1, typename T2> std::vector<T2*> cast_array(const std::vector<T1>& L1){
        std::vector<T2*> L2;
        for(typename std::vector<T1>::iterator i = L1.begin(); i!=L1.end(); i++)
        {
            T2 e = dynamic_cast<T2*>(i);
            // if i was possible to cast && if they don't have the same coordinates
            if (!(e==nullptr)){
                L2.push_back(e);
            }
        }
        return L2;
    }

}


//extern int number_creatures;
//extern int number_creatures_alive;
//extern int number_creatures_dead;
class Creature : public LivingBeing {



public:

    //oskar
    double last_ox = 0;
    double last_oy = 0;
    bool random = false;
    static int n_families;

    // positive double, positive double, positive double, [0, 1], Bool, Bool, positive double, positive double
    enum Enum_parameters{ physical_strength, Max_energy, eye_sight, visibility, eat_creature, eat_plants, Max_hp, size, last};

    // for bool values they ll eaither be 0 or not (thus a smooth conversion, normally)


    // the 'last' parameter is  just there in order to make iteration easier, it has no actual purpuse
    // see https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum

    // CONSTRUCTOR
    // default constructor that creates a creature with random parameters
    // and a default brain
    Creature(bool newfamily = true);


    Creature(Environment *e);
    // non-default constructor that takes a std::map<Enum_parameters, double> and a Network
    Creature(std::map<Enum_parameters, double>, Network*, Environment *e);
    //This is what we'll use to prevent creatures to spawn one on another
    bool Check_Overlap_Creature(Environment* e);
    ~Creature();

    void Eat();

    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    // MEMBER FUNCTIONS
    Creature* reproduction();


    virtual std::vector<LivingBeing*> get_close();

    void eat(LivingBeing &l, double speed);
    void move(double rotation, double distance);
    void take_dmg(double dmg);
    void attack(); // attack will only be an action, we'll be able to attack even if there isn't anything in front
    void die(); // changes the bool alive to false if necessary ( bool declared in LB)
    void is_eaten(Creature &c); //contrary to plants, creatures HAVE TO BE DEAD in order to be eaten
    // the stock of energy in the corpse decreases , reverse function of eat without the eat_time,
    //the loss of energy depends on the size and the diet of the creature WHICH IS EATING

    void move_away(); //for each creature we look for creatures so close that we push them back from each other (when they intersect)

    double get_parameter(Enum_parameters p);
    LivingBeing* find_food();
    //in decision we check if there is actually food (bool found_food) before eating
    void decision(std::vector<double>input_vector, vector<LivingBeing*> c); //takes as input vector given by the nn, and the closest living beings it sees (may be null pointers)
                                              //for given parameters (see .cpp) and takes a decision given the biggest one
    void sleep(int delta_t);//called by decision to decide to sleep for a time delta_t
    void sleep_step();//sleeps for one step : += energy and -= sleep_time
    void playstep();//first tries to : die, sleep , digest, or takes a decison

    void digest(LivingBeing &food, double eat_time);
    void digest_step();
    void bound_energy_hp();   //called in playstep
    void check_if_lack(); //called in playstep , checks if does not sleep or eat or digest for 24 steps
    //and if so, decreases energy and phys strength
    void counter_attack(); //called in playstep - returns the n of turns before the creature was attck (bounded to 100)


    // DATA MEMBERS
    std::map<Enum_parameters, double> parameters;
    std::map<Enum_parameters, double> base_parameters; //Those are the parameters we use for reproduction


    //Vision is simulated using multiple rays which will start from the creature trying to see an go on multiple dircetion.
    // n >=0 correspond to the number of ray we will use to get the vision.
    //The see function will return a vector of size 3*n containing the distance, the size and hp of the first living_being (only distance for non_living beings) that ta ray collide with.
    std::vector<double> See(int n);
    std::vector<double> See(int n, int i); // Auxilary function for See(int)

    vector<double> get_params(LivingBeing* l);
    void move_to(LivingBeing* other, double d);
    std::vector<std::tuple<double,LivingBeing*>> get_closest(int n); // get the closest n things to the creature (distance, size, type, family)

    void set_energy(double e);
    double get_energy() const;
    void set_physical_strength(double ps);
    double get_physical_strength() const;
    void set_eye_sight(double es);
    double get_eye_sight() const;
    void set_visibility(double v);
    double get_visibility() const;
    void set_Max_energy(double me);
    double get_Max_energy() const;
    bool get_eat_creature() const;
    bool get_eat_plants() const;
    void set_Max_hp(double mh);
    double get_Max_hp() const;
    void set_hp(double h);
    double get_hp();
    int get_digest_time();
    void set_digest_time(int time);
    std::vector<double> get_food_attributes();
    void set_food_attributes(LivingBeing &f);
    void set_size(double s);
    double get_size() const;
    bool get_found_food();
    void set_found_food(bool b);
    int get_counter_no_sleep();
    int get_counter_no_eat();
    void set_counter_no_eat(int i);
    void set_counter_no_sleep(int j);
    Network* get_brain();
    void set_brain(Network* b);
    int get_last_attack();
    void set_last_attack(int i);

    void set_family(int f);
    int get_family();

    //this function will be used to detect if two creatures have similar attributes and can be considered as from the same spiecie. This will help us removing some of the problem we had with children eating there parents
    bool same_spiecie(Creature* c);

    void try_reproduce();

    void stay_in_bounds();
    void normal_distrib_random_edge(Edge& edge);
    std::function<double(double)>normal_distrib_random();
    QRectF boundingRect() const;
    bool i_eat_plants;
    bool i_eat_creatures;
    double my_size;
protected:

    int counter_no_reproduction=0;
    LivingBeing* closest = nullptr;
    double repro_factor = 0;
    int family = 0;
    std::vector<double> Input_saved; //This is what we'll use to make our creature know what it had the previous turn
    Network * brain;
    int see_ray = 9;
    bool found_food;//false by default, set to true when found food (plant or creature) and then false again after food is eaten
    double energy;
    double hp;
    std::vector<double>input_vector;//outputed by the NN , to take as input in decision
    double sleep_time=0;
    int digest_time=0;
    std::vector<double> food_attributes; // food attributes of what the creature is currently digesting
    int counter_no_sleep;  //useful for check_if_lack function called in playstep()
    int counter_no_eat;    //initialized at 0
    //if necessary, counters are increased in playstep or digest-step or sleep_step and set to 0 in sleep_step or eat or digest_step
    int last_attack;
    QImage deer=QImage(":/designs/deer.png");
    QImage gazelle=QImage(":/designs/gazelle.png");
    QImage lion=QImage(":/designs/lion.png");
    QImage wolf=QImage(":/designs/wolf.png");
    QGraphicsColorizeEffect *effect;
    QColor bodycolor;
};



#endif // CREATURE_H
