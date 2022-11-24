#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

//Overloading the [] operator, returns the i-th neuron
Neuron Layer :: operator[](int i){
    if(i >= nodes.size()){
        throw std::out_of_range ("Index out of range");
        //cout << "Index out of range. Exiting";
        //exit(0);
        }
    return nodes[i];}

void Layer :: remove_node(int index){
    nodes.erase(nodes.begin() + index);} //Natali: fixed indexing issue here
void Layer :: add_node(Neuron node){
    nodes.push_back(node);
}

int Layer::size(){
    return nodes.size();
}