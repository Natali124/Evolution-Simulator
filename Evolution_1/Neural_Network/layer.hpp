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
    Layer(vector<Neuron> nodes);

    //Other functions
    Neuron operator[](int i);

    void remove_node(int index); // removes node at given index 
    void add_node(Neuron node);    // adds node
    int size();
    
    double f_activation(double x){ //default
    return 1/(pow(M_E, -x) + 1);
    }

private:
    vector<Neuron> nodes;
    Neuron bias_node; };