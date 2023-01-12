#include "layer.hpp"
#include <functional>
#include <iostream>
#include <string>

#pragma once

class Network{ //network with 3 layers


public:
    Network();
    Network(bool randomize);
    Network(int n_input, int n_output, int n_hidden_layers = 2, int n_neurons_in_hidden = 3);
    /* n_input: number of inputs, i.e size of input vector, eqv. to size of input_layer
       n_output: number of outputs, i.e size of output vector, eqv. to size of output_layer
       n_hidden_layers: number of hidden layers
       n_neurons_in_hidden: size of hidden layers*/


    ~Network();
    //getters:
    Layer* get_input_layer();
    Layer* get_output_layer();
    std::vector <Layer*> get_hidden_layers();
    int size();
    //setters:
    void set_input_layer(Layer* input_layer);
    void set_output_layer(Layer* output_layer);
    void set_hidden_layers(std::vector<Layer*> hidden_layers);

    //functions:
    std::vector <double> propagate(std::vector<double>input_vector);
    void randomize_edges();
    void add_layer(int n_nodes);
    void add_layer(int i, int n_nodes, double (*f_activation)(double));
    void add_layer(int i, int n_nodes, act_function f_activation);
    void remove_layer();
    void propagate();
    void apply_on_all_edges(std::function<void(Edge&)> edge_function);
    void apply_on_all_weights(std::function<double(double)> weight_function);
    Network* copy();
    Layer* operator[](int i);
    Network* reproduce();
    //Printing
    void print_adj_list(); // Prints Network represented as adjecency list
    void print_weights(); // Prints weights of the Netwotk
    void print_values();

    //Saving
    std::vector<std::vector<double>> network_to_vector();
    void network_to_file(std::string filename);



private:
    Layer* output_layer;
    Layer* input_layer;
    std::vector <Layer*> hidden_layers;
};



