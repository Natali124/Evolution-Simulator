#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"
#include <vector>
using namespace std;

int Neuron::neuron_counter = 0;

//Constructors
Neuron::Neuron(){
    previous_edges = vector<Edge*>(0);
    next_edges = vector<Edge*>(0);
    parent_layer =nullptr;
    neuron_id = neuron_counter;
    neuron_counter += 1;

}

Neuron::Neuron(vector<Edge*> previous_edges, Layer* parent_layer):Neuron(){
    
        this->previous_edges = previous_edges;
        this->parent_layer = parent_layer;

}

Neuron:: Neuron(Layer* parent_layer):Neuron(){
        this ->parent_layer = parent_layer;
        previous_edges = vector<Edge*>(0);
        }



Neuron:: ~Neuron(){
    neuron_counter-=1;
};
//Getters
vector<Edge*> Neuron :: get_previous_edges(){
    return previous_edges;}

vector<Edge*> Neuron :: get_next_edges(){
    return next_edges;}

vector<double> Neuron::get_next_weights(){
    vector<double> weights;

    for(Edge* edge: next_edges){
        weights.push_back(edge->get_weight());}
    return weights;}
    

int Neuron:: get_id(){
    return neuron_id;}


//Setters
void Neuron::set_next_edges(vector<Edge*> edges){
  next_edges = edges;
}

void Neuron::set_previous_edges(vector<Edge*> edges){
  previous_edges = edges;
}

void Neuron::set_value(double value){
  this->value = value;
}

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



