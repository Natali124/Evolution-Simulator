#ifndef PLANT_H
#define PLANT_H
#include "living_being.h"
#include <map>
#include "creature.h"

class Plant : public LivingBeing
{
public:
    // the enum_parameters is the enumeration that lists the parameters
    // (we overwrite if for the different creatures)
    enum Enum_parameters{reproduction_rate, size, Max_hp, Max_size, last};
    // the 'last' parameter is  just there in order to make iteration easier, it has no actual purpuse
    // see https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum

    // CONSTRUCTORS
    // the defaul constructor initialises parameters with some random values and initializes the size at 1 and hp at max_hp
    Plant();

    // this constructor take a std::map<Enum_parameters, double> and creates a creature with such parameters,
    //initializes the size at 1 and hp at max_hp
    Plant(std::map<Enum_parameters, double> parameters);

    ~Plant();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // DATA MEMBERS
    std::map<Enum_parameters, double> parameters;
    std::map<Enum_parameters, double> base_parameters; //Those are the parameters we use for reproduction

    void playstep(); //increases size and hp, should add reproduction

    double get_reproduction_rate();
    void set_reproduction_rate(double rr);
    double get_size() const;
    void set_size(double s);
    double get_Max_hp() const;
    void set_Max_hp(double hp);
    double get_Max_size() const;
    void set_Max_size(double s);
    double get_hp() const;
    void set_hp(double hp);

    enum Type_Plant{
    Carbs = 0, Protein = 1 , Slimming = 2 , Allergenic = 3 , Allergenic_Protein = 4 , Allergenic_Carbs = 5 ,
        Slimming_Protein = 6, Slimming_Carbs = 7,
    };

    Type_Plant type_plant;

    // MEMBER FUNCTIONS
    LivingBeing* reproduction();

    //functions about a creature eating a plant:impact on physical_strength, energy, visibility and eye_sight.
    //variables are incremented/ decremented by a coefficient alpha which depends on the
    // difference between the size of the plant and the size of the creature. The higher this difference is,
    // the less the plant will have an effect on the creature's body.
    // not in coding language: alpha = 1 - (1/ dif(c_size , plant_size))
    // ++ or -- means + or - 2*alpha
    void is_eaten(Creature &c);


    void take_dmg(double dmg);
//to update using the future get and set functions for c.parameters
    double get_alpha(Creature &c);
    void carbs(Creature &c);   // + energy , - strength (c becomes heavier)
    void protein(Creature &c); // + strength, - energy (hard to digest)
    void slimming_effect(Creature &c);// + eye_sight, - visibility (c becomes slimmer,easier to move the head)
    void allergenic_effect(Creature &c);// + visibility, - eye_sight (c has an allergic reaction: body swells)
    void allergenic_protein(Creature &c);// ++ strength , - energy and - visibility
    void allergenic_carbs(Creature &c);// ++ energy, - strength and - eye_sight
    void slimming_protein(Creature &c);//++ strength , - energy and - visibility
    void slimming_carbs(Creature &c);// ++ energy, - strength and - visibility

protected:
    int repro_count = 0;
    double hp;

};

#endif // PLANT_H
