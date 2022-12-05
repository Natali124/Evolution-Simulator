#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"
#include <vector>
using namespace std;


//Constructors
Neuron::Neuron(){
    previous_edges = vector<Edge*>(0);
    next_edges = vector<Edge*>(0);
    parent_layer =nullptr;
    neuron_counter += 1;

}

Neuron::Neuron(vector<Edge*> previous_edges, Layer* parent_layer){
    
        this ->previous_edges = previous_edges;
        this ->parent_layer = parent_layer;
        neuron_counter += 1;

}

Neuron:: Neuron(Layer* parent_layer){        
        this ->parent_layer = parent_layer;
        previous_edges = vector<Edge*>(0);
        neuron_counter += 1;        
        }



Neuron:: ~Neuron(){
    neuron_counter-=1;
};
//Getters
vector<Edge*> Neuron :: get_previous_edges(){
    return previous_edges;}

vector<Edge*> Neuron :: get_next_edges(){
    return next_edges;}


//Other functions
void Neuron::add_edge(Edge* edge, bool previous){
    if(previous){
        previous_edges.push_back(edge);}
    else{
        next_edges.push_back(edge);}}


void Neuron::forward_propagate(){
    double sum = 0;
    for (int i = 0; i < previous_edges.size(); i ++){
        sum += (*previous_edges[i]).get_weight() * (*previous_edges[i]).get_start_neuron()->value;
    }

    value = parent_layer->f_activation(sum);
}

// Function added for compilation reasons (Vincenzo)
double Neuron::get_value(){return (double)0;};
void Neuron::set_value(double value){};
Neuron::~Neuron(){};


