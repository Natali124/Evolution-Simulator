#include "edge.hpp"
#include <random>
#include <ctime>
#include <cstdlib>

Edge::Edge(){
        weight = 0;
        start_neuron = nullptr;
        end_neuron = nullptr;
        is_active = true;
    }
Edge::Edge(double w):Edge(){
        weight = w;
    }
Edge::Edge(double w, Neuron* start, Neuron* end):Edge(){
        weight = w;
        start_neuron = start;
        end_neuron = end;
    }
void Edge::randomize_weight(){
        srand((int)time(0));
        double r = (double) rand() / RAND_MAX;
        r = r*2 - 1;
        set_weight(r);
    }
double Edge::get_weight(){
        return weight;
    }
Neuron* Edge::get_start_neuron(){
        return start_neuron;
    }
Neuron* Edge::get_end_neuron(){
        return end_neuron;
    }
bool Edge::get_is_active(){
    return is_active;
}
void Edge::set_weight(double w){
        weight = w;
    }
void Edge::set_start(Neuron* n){
        start_neuron = n;
    }
void Edge::set_end(Neuron* n){
        end_neuron = n;
    }

void Edge::set_activation(bool activation){
    is_active = activation;}