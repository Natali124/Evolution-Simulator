#include "edge.hpp"
#include "neuron.hpp"
#include <random>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

Edge::Edge(){
        weight = 0;
        start_neuron = nullptr;
        end_neuron = nullptr;
        is_active = true;
    }
Edge::Edge(double w):Edge(){
        weight = w;
    }
Edge::Edge(Neuron* start, Neuron* end):Edge(){
        start_neuron = start;
        end_neuron = end;
    }
Edge::Edge(double w, Neuron* start, Neuron* end):Edge(start,end){
         weight = w;
    }
void Edge::randomize_weight(){
        srand((int)time(0));
        double r = (double) rand() / RAND_MAX;
        r = r*2 - 1;
        set_weight(r);
    }

void Edge::print(){
  std::cout << start_neuron->get_id() << " ---" << weight << "--- " << end_neuron->get_id() << std::endl;
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

int Edge:: get_end_neuron_id(){
    return end_neuron->get_id();
}
int Edge:: get_start_neuron_id(){
    return start_neuron->get_id();
}
bool Edge::get_is_active(){
    return is_active;
}
void Edge::set_weight(double w){
        weight = w;
    }
void Edge::set_start_neuron(Neuron* n){
        start_neuron = n;
    }
void Edge::set_end_neuron(Neuron* n){
        end_neuron = n;
    }

void Edge::set_activation(bool activation){
    is_active = activation;}
