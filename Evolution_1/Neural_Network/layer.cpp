#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

//Constructors
Layer::Layer(){
  *bias_neuron = Neuron();
  neurons = vector<Neuron*>(0);
}
Layer::Layer(vector<Neuron*> neurons):Layer(){
  this->neurons = neurons;
}

Layer::Layer(int n_neurons):Layer(){
  vector<Neuron*> v(0);
  for (int i = 0; i < n_neurons; i++){
    Neuron n = Neuron();
    v.push_back(&n);
  }
  neurons = v;
}

Layer::Layer(int n_neurons, act_function act_func):Layer(){
    vector<Neuron*> v(0);
    for (int i = 0; i < n_neurons; i++){
      /** This is bad!
      Neuron* new_neuron;
      *new_neuron = Neuron();
      v.push_back(new_neuron); **/

      // This is good:
      Neuron new_neuron = Neuron();
      v.push_back(&new_neuron);
     }
    neurons = v;
}



//Overloading the [] operator, returns the i-th neuron
Neuron* Layer :: operator[](int i){
    if(i >= neurons.size()){
        throw std::out_of_range ("Index out of range");
        }
    return neurons[i];}


// Manipulation
vector<double> Layer::get_values(){
  // Returns values of Neurons in Layer as vector of doubles
  vector<double> v = vector<double>(0);
  for(auto & neuron : neurons){
      v.push_back(neuron->get_value());
    }
  return v;
}
void Layer::set_values(vector<double> v){
  // sets values of each neuron of layer
  // to corresponding value in input vector
  if(v.size() != neurons.size()){
      throw; // if size doesn't match, throw exception
  } else {
    for(int i=0; i< neurons.size(); i++){
      neurons[i]->set_value(v[i]);
    }
  }
}

vector<Neuron*> Layer::get_neurons(){
  {return neurons;}
}

void Layer :: remove_neuron(int index){
    neurons.erase(neurons.begin() + index);}
void Layer :: add_neuron(Neuron* node){
    neurons.push_back(node);}
int Layer::size(){
    return neurons.size();
}
void Layer :: set_activation_function(act_function func){
  f_activation_name = func;
}


void Layer::fully_connect(Layer* prev_layer){
  // connects all Neurons of this layer to all
  // neurons of given prev_layer (previous layer)
  // randomized weights on all edges
  for(auto & current_neuron : neurons){
      // Connect to bias neuron of previous layer
      Neuron* prev_neuron = prev_layer->bias_neuron;
      Edge edge = Edge(&(*prev_neuron), &(*current_neuron));
      prev_neuron->add_edge(&edge,true);
      current_neuron->add_edge(&edge,false);

      // Connect to all neurons of previous layer
      for(auto & prev_neuron : prev_layer->neurons){
          Edge edge = Edge(&(*prev_neuron), &(*current_neuron));
          prev_neuron->add_edge(&edge,true);
          current_neuron->add_edge(&edge,false);
        }
    }
}

// Added for compilation reasons (Vincenzo)
Layer::~Layer(){};
// define activation functions, same name as in enum act_function, but all lowercase
double sigmoid(double x){return 1/(pow(M_E, -x) + 1);};
double relu(double x){return fmax(0, x);};

// map (=dictionary) to get specific function from enum
map<act_function,function<double(double)>> get_f_activation_from_name = {{Sigmoid,&sigmoid},{ReLu,&relu}};


double Layer::f_activation(double x){
  return get_f_activation_from_name[f_activation_name](x);
}
