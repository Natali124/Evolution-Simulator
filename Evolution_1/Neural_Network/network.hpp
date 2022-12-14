#include "layer.hpp"
#include <functional>
#pragma once

class Network{ //network with 3 layers


// can you do a default constructor please? Cause I need one for Creature class (Garance)
public:
    Network(bool randomize = true);
    Network(int n_input, int n_output, int n_hidden_layers = 2, int n_neurons_in_hidden = 3);
    ~Network();
    //getters:
    Layer* get_input_layer();
    Layer* get_output_layer();
    vector <Layer*> get_hidden_layers();

    //setters:
    void set_input_layer(Layer* input_layer);
    void set_output_layer(Layer* output_layer);
    void set_hidden_layers(vector<Layer*> hidden_layers);

    //functions:
    vector <double> propagate(vector<double>input_vector);
    void randomize_edges();
    void add_layer(int n_nodes);
    void add_layer(int i, int n_nodes, double (*f_activation)(double));
    void add_layer(int i, int n_nodes, act_function f_activation);
    void remove_layer();
    void propagate();
    void apply_on_all_edges(function<void(Edge&)> edge_function);
    void apply_on_all_weights(function<double(double)> weight_function);
    Network copy();

    //Printing
    void print_adj_list(); // Prints Network represented as adjecency list
    void print_weights(); // Prints weights of the Netwotk
    void print_values();


private:
    Layer* output_layer;
    Layer* input_layer;
    vector <Layer*> hidden_layers;
};
