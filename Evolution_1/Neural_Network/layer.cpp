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
        //cout << "Index out of range. Exiting";
        //exit(0);
        }
    return neurons[i];}

void Layer :: remove_neuron(int index){
    neurons.erase(neurons.begin() + index);} //Natali: fixed indexing issue here

void Layer :: add_neuron(Neuron neuron){
    neurons.push_back(neuron);
}

int Layer::size(){
    return neurons.size();
}
