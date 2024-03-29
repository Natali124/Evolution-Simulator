#include "edge.hpp"
#include "neuron.hpp"
#pragma once

#include <cmath>
#include <vector>
#include <map>
#include <functional>
using namespace std;

class Neuron;
class Edge;
class Network;

// Enumerate variable for activation functions
enum act_function{Sigmoid, ReLu};


class Layer{
public:
    // Constructors
    Layer();
    Layer(vector<Neuron*> neurons);
    Layer(int n_neurons);
    Layer(int n_neurons, act_function f_activation); //after enum is done
    ~Layer();

    // Getters and Setters, Manipulation
    vector<double> get_values();
    vector<Neuron*> get_neurons();
    Neuron* get_bias_neuron();
    act_function get_activation_function(); // Get the activation function
    int get_index(Network* n); // index of layer in network (0 = input_layer, ...)

    void set_values (vector <double> v);
    void set_activation_function(act_function func); // Set the activation function

    void add_neuron(Neuron* neuron); // adds Neuron to end of array
    void remove_neuron(int index);  // removes Neuron at given index

    int size();
    
    //Other functions
    Neuron* operator[](int i); // implement [] access operator for Layer
    void fully_connect(Layer* prev_layer); //fully connects Layer to previous layer, randomized weights
    void disconnect(bool previous); // disconects layer to either previous or next layer as indicated by previous
    double f_activation(double x);

    void print_edges();

    //Helper functionsfor saving
    vector<double> layer_to_vector(); //constructs vector containing edges
    vector<double> value_vector(); //constructs vector containing vaules of neurons


private:
    vector<Neuron*> neurons;
    Neuron* bias_neuron;

    act_function f_activation_name;

};


 
