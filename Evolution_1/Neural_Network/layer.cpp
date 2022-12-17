#include "edge.hpp"
#include "neuron.hpp"
#include "layer.hpp"

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

//Constructors
Layer::Layer(){
  //Neuron* n = new Neuron(this);
  bias_neuron = new Neuron(this);
  bias_neuron->set_value(1);
  neurons = vector<Neuron*>(0);
  f_activation_name = Sigmoid;
}
Layer::Layer(vector<Neuron*> neurons):Layer(){
  this->neurons = neurons;
}

Layer::Layer(int n_neurons):Layer(){
  vector<Neuron*> v(0);
  for (int i = 0; i < n_neurons; i++){
    //Neuron* n = new Neuron(this);
    v.push_back(new Neuron(this));
  }
  neurons = v;
}

Layer::Layer(int n_neurons, act_function act_func):Layer(n_neurons){
    this->f_activation_name = act_func;
}



//Overloading the [] operator, returns the i-th neuron
Neuron* Layer :: operator[](int i){
    if(i< 0 or i >= neurons.size()){
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
Neuron* Layer::get_bias_neuron(){
  return bias_neuron;
}

void Layer :: remove_neuron(int index){
    Neuron* neur = neurons.at(index);
    neurons.erase(neurons.begin() + index);
    delete neur;
}
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
      Edge* edge = new Edge(&(*prev_neuron), &(*current_neuron));
      prev_neuron->add_edge(edge,false);
      current_neuron->add_edge(edge,true);

      // Connect to all neurons of previous layer
      for(auto & prev_neuron : prev_layer->neurons){
          Edge* edge = new Edge(&(*prev_neuron), &(*current_neuron));
          prev_neuron->add_edge(edge,false);
          current_neuron->add_edge(edge,true);
        }
    }
}

void Layer::disconnect(bool previous){
    if(previous){
        for(Neuron* neuron: neurons){
            for(Edge* edge: neuron->get_previous_edges()){
                Neuron* prev_neuron = edge->get_start_neuron();
                neuron->remove_edge(edge, true);
                prev_neuron->remove_edge(edge, false);
            }
            neuron->set_previous_edges(vector<Edge*>(0));
            }}
    else{
        for(Neuron* neuron: neurons){
            for(Edge* edge: neuron->get_next_edges()){
                Neuron* prev_neuron = edge->get_end_neuron();
                neuron->remove_edge(edge, false);
                prev_neuron->remove_edge(edge, true);
            }
            neuron->set_next_edges(vector<Edge*>(0));}}}

vector<double> Layer::layer_to_vector(){
/* Each layer will be saved as follows: for each edge, the weght and the activation is stored.
 The last number of the vector is the activation function*/
    vector<double> output(0);
    for(Neuron* neuron: neurons){
        for(Edge* edge: neuron->get_next_edges()){
            output.push_back(edge->get_weight());

            if (edge->get_activation()){
             output.push_back(0);}
            else{
                output.push_back(1);}}}
    output.push_back(f_activation_name);}



// Added for compilation reasons (Vincenzo)
Layer::~Layer(){
  delete bias_neuron;
  for(auto &neuron : neurons){
      delete neuron;
    }
};

// define activation functions, same name as in enum act_function, but all lowercase
double sigmoid(double x){return 1/(pow(M_E, -x) + 1);};
double relu(double x){return fmax(0, x);};

// map (=dictionary) to get specific function from enum
map<act_function,function<double(double)>> get_f_activation_from_name = {{Sigmoid,&sigmoid},{ReLu,&relu}};


double Layer::f_activation(double x){
  return get_f_activation_from_name[f_activation_name](x);
}

void Layer::print_edges(){
  for(Neuron* neuron: neurons){
   cout << neuron->get_id() << ": ";
   for(double weight: neuron->get_next_weights()){
      cout << round(weight*100)/100 << " " ;
  }
  cout<<" \n";}

  cout << bias_neuron->get_id() << "(b): ";
  for(double weight: bias_neuron->get_next_weights()){
     cout << round(weight*100)/100 << " " ;
  }
  cout << "\n";
}
