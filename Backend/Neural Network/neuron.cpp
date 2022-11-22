#include "edge.hpp"
#include "edge.cpp"
#include "neuron.hpp"
#include <cmath>
#include <vector>
using namespace std;

class Neuron{
public:
    double get_value(){
        return value;
    }
    void forward_propagate(); //updates neuron based on neurons of the previous layer
    vector <Edge> input_edges;
    double f_activation(double x); //sigmoid function
private:
    double value;

};

void Neuron::forward_propagate(){
    double sum = 0;
    for (int i = 0; i < input_edges.size(); i ++){
        sum += input_edges[i].get_weight() * input_edges[i].get_start_neuron()->value;
    }
    value = f_activation(sum);
}

double Neuron::f_activation(double x){
    return 1/(pow(M_E, -x));
}