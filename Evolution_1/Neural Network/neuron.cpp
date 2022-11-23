#include "edge.hpp"
#include "edge.cpp"
#include "neuron.hpp"
#include "layer.hpp"
#include "layer.cpp"
#include <vector>
using namespace std;

void Neuron::forward_propagate(){
    double sum = 0;
    for (int i = 0; i < input_edges.size(); i ++){
        sum += input_edges[i].get_weight() * input_edges[i].get_start_neuron()->value;
    }
    value = layer.f_activation(sum);
}