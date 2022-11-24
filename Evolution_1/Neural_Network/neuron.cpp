#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"
#include <vector>
using namespace std;


//Constructors

Neuron::Neuron(int neuron_id, vector<Edge> previous_edges, Layer layer){
        this->neuron_id = neuron_id;
        this ->previous_edges = previous_edges;
        this ->layer = layer;
        inputs = vector(0);

}

Neuron:: Neuron(int neuron_id, stdvector<double> inputs, Layer layer){
        this->neuron_id = neuron_id;
        this ->inputs = inputs;
        this ->layer = layer;
        }


vector<double> Neuron :: get_inputs(){
    return inputs;}

vector<Edge> Neuron :: get_previous_edges(){
    return previous_edges;}

vector<Edge> Neuron :: get_next_edges(){
    return next_edges;}

void add_edge(Edge edge, bool previous){
    if(previous){
        previous_edges.push_back(edge);}
    else{
        next_edges.push_back(edge);}}


void Neuron::forward_propagate(){
    double sum = 0;
    for (int i = 0; i < previous_edges.size(); i ++){
        sum += previous_edges[i].get_weight() * previous_edges[i].get_start_neuron()->value;
    }
    value = layer.f_activation(sum);
}