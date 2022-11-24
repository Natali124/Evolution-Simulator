#include "layer.hpp"
#pragma once



class Network{ //network with 3 layers


// can you do a default constructor please? Cause I need one for Creature class (Garance)
public:
    Network();
    ~Network();
    vector <double> propagate(vector<double>input_vector);
    void randomize_edges();
    void add_layer(int n_nodes);
    void add_layer(int i, auto f_activation, int n_nodes);
    void remove_layer();
    void propagate();
private:
    Layer input_layer;
    Layer output_layer;
    vector <Layer> hidden_layers;
};
