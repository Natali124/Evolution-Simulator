#include "layer.hpp"
#include <functional>
#pragma once

class Network{ //network with 3 layers


public:
    Network(bool randomize = true);
    Network(int n_input, int n_output, int n_hidden_layers = 2, int n_neurons_in_hidden = 3);
    ~Network();
    //getters:
    Layer* get_input_layer();
    Layer* get_output_layer();
    std::vector <Layer*> get_hidden_layers();

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
    Network copy();

    //Printing
    void print_adj_list(); // Prints Network represented as adjecency list
    void print_weights(); // Prints weights of the Netwotk
    void print_values();


private:
    Layer* output_layer;
    Layer* input_layer;
    std::vector <Layer*> hidden_layers;
};
