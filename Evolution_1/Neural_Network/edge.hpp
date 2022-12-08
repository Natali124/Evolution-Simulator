#pragma once

class Neuron; 

class Edge{
public:
    //Constructors & destructor

    Edge();
    Edge(double w);
    Edge(Neuron* start, Neuron* end);
    Edge(double w, Neuron* start, Neuron* end);
    ~Edge(){};

    //Specific functions

    void randomize_weight();

    //Getters

    double get_weight();
    Neuron* get_start_neuron();
    Neuron* get_end_neuron();
    int get_next_neuron_id();
    bool get_is_active();

    //Setters

    void set_weight(double w);
    void set_start_neuron(Neuron* n);
    void set_end_neuron(Neuron* n);
    void set_activation(bool activation);

private:
    double weight;
    Neuron* start_neuron;
    Neuron* end_neuron;
    bool is_active = true;

};
