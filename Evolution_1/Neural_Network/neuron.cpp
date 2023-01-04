#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"
#include "utils.cpp"
#include "network.hpp"
#include <vector>
//using namespace std;

int Neuron::neuron_counter = 0;

//Constructors
Neuron::Neuron(){
    previous_edges = std::vector<Edge*>(0);
    next_edges = std::vector<Edge*>(0);
    parent_layer = nullptr;
    neuron_id = neuron_counter;
    neuron_counter += 1;

}

Neuron::Neuron(std::vector<Edge*> previous_edges, Layer* parent_layer):Neuron(){
    
        this->previous_edges = previous_edges;
        this->parent_layer = parent_layer;

}

Neuron:: Neuron(Layer* parent_layer):Neuron(){
        this ->parent_layer = parent_layer;
        previous_edges = std::vector<Edge*>(0);
        }


// Destructors
Neuron:: ~Neuron(){
    //neuron_counter-=1;

    // Deletes all edges associated to neuron
    for (Edge* e : previous_edges) {
        e->get_start_neuron()->remove_edge(e,false);
        delete e;
      }
    for (Edge* e : next_edges) {
        e->get_end_neuron()->remove_edge(e,true);
        delete e;
      }
};
//Getters
std::vector<Edge*> Neuron :: get_previous_edges(){
    return previous_edges;}

std::vector<Edge*> Neuron :: get_next_edges(){
    return next_edges;}

std::vector<double> Neuron::get_next_weights(){
    std::vector<double> weights;

    for(Edge* edge: next_edges){
        weights.push_back(edge->get_weight());}
    return weights;}
    

int Neuron:: get_id(){
    return neuron_id;}

double Neuron::get_value(){
    return value;}

int Neuron::get_index(){
    // returns index of neuron in parent layer, bias_neuron is last index

    int i =  find_index<Neuron*>(parent_layer->get_neurons(),this);
    if(i!= -1){
        return i;
      } else {
        return parent_layer->size()-1;
      }
}

void Neuron::get_full_index(Network* n, int& i, int& j){
    i = parent_layer->get_index(n);
    j = this->get_index();
}

//Setters
void Neuron::set_next_edges(std::vector<Edge*> edges){
  next_edges = edges;
}

void Neuron::set_previous_edges(std::vector<Edge*> edges){
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

void  Neuron:: remove_edge(int index, bool previous){
    if(previous){
        Edge* to_erase = previous_edges[index]; //edge to be erased
        Neuron* prev_neuron = to_erase->get_start_neuron();
        if(prev_neuron != nullptr){
            prev_neuron->remove_edge(to_erase, false);}
        previous_edges.erase(previous_edges.begin() + index);}
    else{
        Edge* to_erase = next_edges[index]; //edge to be erased
        Neuron* prev_neuron = to_erase->get_end_neuron();
        if(prev_neuron != nullptr){
            prev_neuron->remove_edge(to_erase, true);}
        next_edges.erase(next_edges.begin() + index);}
    }

void Neuron::remove_edge(Edge* edge, bool previous){

    if(previous){
        int n = previous_edges.size();
        for(int i = 0; i < n; i ++){
            if(previous_edges[i] == edge){
                 previous_edges.erase(previous_edges.begin() + i);
                 break;}}}
    else{
        int n = next_edges.size();
        for(int i = 0; i < n; i ++){
            if(next_edges[i] == edge){
                 next_edges.erase(next_edges.begin() + i);
                 break;}}}
}



void Neuron::forward_propagate(){
    double sum = 0;
    for (int i = 0; i < previous_edges.size(); i ++){
        sum += (*previous_edges[i]).get_weight() * (*previous_edges[i]).get_start_neuron()->value;
    }

    value = parent_layer->f_activation(sum);
}

// Function added for compilation reasons (Vincenzo)
//void Neuron::set_value(double value){};



