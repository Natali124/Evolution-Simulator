#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

//Overloading the [] operator, returns the i-th neuron
Neuron Layer :: operator[](int i){
    if(i >= neurons.size()){
        throw std::out_of_range ("Index out of range");
        }
    return neurons[i];}

void Layer :: remove_neuron(int index){
    neurons.erase(neurons.begin() + index);}
void Layer :: add_neuron(Neuron node){
    neurons.push_back(node);
}

int Layer::size(){
    return neurons.size();
}
