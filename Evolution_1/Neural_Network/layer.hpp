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
    Layer(vector<Neuron> neurons);

    //Other functions
    Neuron operator[](int i);
    void set_values (vector <double> v);

    void remove_neuron(int index); // removes Neuron at given index
    void add_neuron(Neuron neuron);    // adds Neuron
    int size();
    
    double f_activation(double x){ //default
    return 1/(pow(M_E, -x) + 1);
    }

private:
    vector<Neuron> neurons;
    Neuron bias_neuron;
};
