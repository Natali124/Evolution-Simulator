#ifndef CREATURE_H
#define CREATURE_H
#include "living_being.h"
#include "Neural_Network/network.hpp"
#include <iostream>
#include <vector>
#include <map>


//This namespace will be used in order to have some more object to use:
namespace Other {
    //We"ll use this class to detect what's in front of what, as an example it could be used to attack, eat, etc...
    class Square: public QGraphicsItem{
    public:
        // base values: 0, 0, 1, 1
        Square();
        Square(qreal X, qreal Y, qreal R, qreal W, qreal H);
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void set_shape();
        qreal w;
        qreal h;
    };


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



class Creature : public LivingBeing {
public:


    // positive double, positive double, positive double, [0, 1], Bool, Bool, positive double, positive double
    enum Enum_parameters{ physical_strength, Max_energy, eye_sight, visibility, eat_creature, eat_plants, Max_hp, size, last};

    // for bool values they ll eaither be 0 or not (thus a smooth conversion, normally)


    // the 'last' parameter is  just there in order to make iteration easier, it has no actual purpuse
    // see https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum

    // CONSTRUCTOR
    // default constructor that creates a creature with random parameters
    // and a default brain
    Creature(Environment* environment = nullptr);
    // non-default constructor that takes a std::map<Enum_parameters, float> and a Network
    Creature(std::map<Enum_parameters, float>, Network);
    ~Creature();

    // MEMBER FUNCTIONS
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void reproduction();
    // functions to be taken care of by Flavia, Garance, Ruben, Oskar, Pablo's team

    virtual std::vector<LivingBeing*> get_close();

    void eat(LivingBeing &l, float speed);
    void move(float rotation, float distance);
    void take_dmg(float dmg);
    void attack(); // attack will only be an action, we'll be able to attack even if there isn't anything in front
    void die(); // changes the bool alive to false if necessary ( bool declared in LB)
    void is_eaten(Creature &c); //contrary to plants, creatures HAVE TO BE DEAD in order to be eaten
    // the stock of energy in the corpse decreases , reverse function of eat without the eat_time,
    //the loss of energy depends on the size and the diet of the creature WHICH IS EATING

    float get_parameter(Enum_parameters p);
    LivingBeing* find_food();
    //in decision we check if there is actually food (bool found_food) before eating
    void decision(vector<float>input_vector); //takes as input vector given by the nn,
                                              //for given parameters (see .cpp) and takes a decision given the biggest one
    void sleep(float delta_t);//called by decision to decide to sleep for a time delta_t
    void sleep_step();//sleeps for one step : += energy and -= sleep_time
    void playstep();//first tries to : die, sleep , digest, or takes a decison

    void digest(LivingBeing &food, float eat_time);
    void digest_step();

    // DATA MEMBERS
    Network brain;
    std::map<Enum_parameters, float> parameters;
    std::map<Enum_parameters, float> base_parameters; //Those are the parameters we use for reproduction

    // n >=0 correspond to the number of ray we will use to get the vision.
    // for now, vision is only in front
    std::vector<float> See(int n);
    std::vector<float> See(int n, int i); // auxilary function for See(int)

    void set_energy(float e);
    float get_energy();
    void set_physical_strength(float ps);
    float get_physical_strength();
    void set_eye_sight(float es);
    float get_eye_sight();
    void set_visibility(float v);
    float get_visibility();
    void set_Max_energy(float me);
    float get_Max_energy();
    bool get_eat_creature();
    bool get_eat_plants();
    void set_Max_hp(float mh);
    float get_Max_hp();
    void set_hp(float h);
    float get_hp();
    int get_digest_time();
    void set_digest_time(int time);
    vector<float> get_food_attributes();
    void set_food_attributes(LivingBeing &f);
    void set_size(float s);
    float get_size();
    bool get_found_food();
    void set_found_food(bool b);


protected:
    bool found_food;//false by default, set to true when found food (plant or creature) and then false again after food is eaten
    float energy;
    float hp;
    vector<float>input_vector;//outputed by the NN , to take as input in decision
    float sleep_time;
    int digest_time;
    vector<float> food_attributes; // food attributes of what the creature is currently digesting
    int species;
};



#endif // CREATURE_H
