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


// Enumerate variable for activation functions
enum act_function{Sigmoid, ReLu};

// define activation functions, same name as in enum act_function, but all lowercase
double sigmoid(double x){return 1/(pow(M_E, -x) + 1);};
double relu(double x){return fmax(0, x);};

// map (=dictionary) to get specific function from enum
map<act_function,function<double(double)>> get_f_activation_from_name = {{Sigmoid,&sigmoid},{ReLu,&relu}};

class Layer{
public:
    // Constructors
    Layer();
    Layer(vector<Neuron*> neurons);
    Layer(int n_neurons);
    Layer(int n_neurons, act_function f_activation); //after enum is done
    ~Layer();

    // Getters and Setters, Manipulation
    void set_values (vector <double> v);
    vector<double> get_values();
    vector<Neuron*> get_neurons(){return neurons;};
    void remove_neuron(int index);  // removes Neuron at given index
    void add_neuron(Neuron* neuron); // adds Neuron to end of array
    int size();
    void set_activation_function(act_function func); // Set the activation function

    
    //Other functions
    Neuron* operator[](int i); // implement [] access operator for Layer
    void fully_connect(Layer* prev_layer); //fully connects Layer to previous layer, randomized weights
    double f_activation(double x){return get_f_activation_from_name[f_activation_name](x);};


private:
    vector<Neuron*> neurons;
    Neuron* bias_neuron;
    act_function f_activation_name;

};


 
