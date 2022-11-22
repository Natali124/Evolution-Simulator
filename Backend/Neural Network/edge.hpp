#include <random>

class Neuron;


class Edge{
public:
    //Constructors & destructor

    Edge();
    Edge(double w);
    Edge(double w, Neuron* start, Neuron* end);
    ~Edge(){};

    //Specific functions

    void randomize_weight();

    //Getters

    double get_weight();
    Neuron* get_start_neuron();
    Neuron* get_end_neuron();

    //Setters

    void set_weight(double w); //also updates prev_weight
    void set_start(Neuron* n);
    void set_end(Neuron* n);

private:
    double weight;
    double prev_weight;
    Neuron* start_neuron;
    Neuron* end_neuron;
};