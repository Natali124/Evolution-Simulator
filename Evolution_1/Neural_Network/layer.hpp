#include "edge.hpp"
#include "neuron.hpp"
#pragma once

#include <cmath>
#include <vector>
using namespace std;

class Neuron;
class Edge;

class Layer{
public:
    // Constructors
    Layer();
    Layer(vector<Neuron*> neurons);
     Layer(int n_neurons);
     Layer(int n_neurons, double (*f_activation)(double)); //after enum is done
    ~Layer();

    // Getters and Setters, Manipulation
    void set_values (vector <double> v);
    vector<double> get_values();
    vector<Neuron*> get_neurons(){return neurons;};
    void remove_neuron(int index);  // removes Neuron at given index
    void add_neuron(Neuron* neuron); // adds Neuron to end of array
    int size();
    
    //Other functions
    Neuron* operator[](int i); // implement [] access operator for Layer
    void fully_connect(Layer* prev_layer); //fully connects Layer to previous layer, randomized weights
    double f_activation(double x){ return 1/(pow(M_E, -x) + 1); }//default

private:
    vector<Neuron*> neurons;
    Neuron* bias_neuron;
};



// Enumerate variable for activation functions 

double Sigmoid(double x);
double ReLu(double x);

enum functions{Sigmoid, ReLu}; 
 