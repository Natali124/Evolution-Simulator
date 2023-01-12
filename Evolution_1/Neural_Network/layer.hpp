#include "edge.hpp"
#include "neuron.hpp"
#pragma once

#include <cmath>
#include <vector>
#include <map>
#include <functional>
//using namespace std;

class Neuron;
class Edge;
class Network;

// Enumerate variable for activation functions
enum act_function{Sigmoid, ReLu};


class Layer{
public:
    // Constructors
    Layer();
    Layer(std::vector<Neuron*> neurons);
    Layer(int n_neurons);
    Layer(int n_neurons, act_function f_activation); //after enum is done
    ~Layer();

    // Getters and Setters, Manipulation
    void set_values (std::vector <double> v);
    std::vector<double> get_values();
    std::vector<Neuron*> get_neurons();
    Neuron* get_bias_neuron();
    void remove_neuron(int index);  // removes Neuron at given index
    void add_neuron(Neuron* neuron); // adds Neuron to end of array
    int size();
    void set_activation_function(act_function func); // Set the activation function
    act_function get_activation_function(); // Get the activation function
    int get_index(Network* n); // index of layer in network (0 = input_layer, ...)

    
    //Other functions
    Neuron* operator[](int i); // implement [] access operator for Layer
    void fully_connect(Layer* prev_layer); //fully connects Layer to previous layer, randomized weights
    void disconnect(bool previous); // disconects layer to either previous or next layer as indicated by previous
    double f_activation(double x);
    void print_edges();

    //Helper function for saving
    vector<double> layer_to_vector();


private:
    std::vector<Neuron*> neurons;
    Neuron* bias_neuron;

    act_function f_activation_name;

};


 
