#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"

#include <cmath>
#include <vector>
using namespace std;

//Overloading the [] operator, returns the i-th neuron
Neuron Layer :: operator[](int i){
    if(i >= nodes.size){
        cout<< "Index out of range. Exiting";
        exit(0)}
    return nodes[i];}

void Layer :: remove_node(int index){
    nodes.erase(index);}
void Layer :: add_node(Node node){
    nodes.push_back(node);
}