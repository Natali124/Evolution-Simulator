#include "layer.hpp"
#include <functional>
#pragma once

class Network{ //network with 3 layers


// can you do a default constructor please? Cause I need one for Creature class (Garance)
public:
    Network();
    ~Network();
    vector <double> propagate(vector<double>input_vector);
    void randomize_edges();
    void add_layer(int n_nodes);
    void add_layer(int i, double (*f_activation)(double), int n_nodes);
    void remove_layer();
    void propagate();
    void apply_on_all_edges(function<void(Edge&)> edge_function);
    void apply_on_all_weights(function<double(double)> weight_function);
private:
    Layer input_layer;
    Layer output_layer;
    vector <Layer> hidden_layers;
};
