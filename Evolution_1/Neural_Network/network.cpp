#include "network.hpp"
#include <vector>
#include <functional>
using namespace std;


vector <double> Network::propagate(vector<double>v){
    // returns output vector for given input vector
    // going through the neural network

    input_layer->set_values(v);
    for (int i = 0; i < hidden_layers.size(); i++){
        for (int j = 0; j < hidden_layers[i]->size(); j++){
            (*hidden_layers[i])[j]->forward_propagate();
        }
    }
    for (int i = 0; i < output_layer->size(); i++){
        (*output_layer[i])->forward_propagate();
    }
    return output_layer->get_values();
}

void Network::randomize_edges(){
    //for each edge call randomize edge.

    // apply to all edges going to any hidden_layer
    for(auto & layer : hidden_layers){
        for(auto & neuron : layer->get_neurons()){
            for(auto & edge : neuron->get_previous_edges()){
              edge->randomize_weight();
            }
        }
    }
    // apply to all edges going to ouput_layer
    for(auto & neuron : output_layer->get_neurons()){
        for(auto & edge : neuron->get_previous_edges()){
            edge->randomize_weight();
          }
      }
}

void Network::apply_on_all_edges(function<void(Edge&)> edge_function){
    // applies a function on all edges of network
    // function changes Edge object directly

    // apply to all edges going to any hidden_layer
    for(auto & layer : hidden_layers){
        for(auto & neuron : layer->get_neurons()){
            for(auto & edge : neuron->get_previous_edges()){
              edge_function(*edge);
            }
        }
    }
    // apply to all edges going to ouput_layer
    for(auto & neuron : output_layer->get_neurons()){
        for(auto & edge : neuron->get_previous_edges()){
            edge_function(*edge);
          }
      }
}

void Network::apply_on_all_weights(function<double(double)> weight_function){
  // applies a function on all weights of the network
  apply_on_all_edges([weight_function](Edge& e) { e.set_weight(weight_function(e.get_weight())); });
}

void Network::remove_layer(){
    //removes the last layer from hidden layers
    hidden_layers.pop_back();
}

void Network::add_layer(int n_nodes){
    //adds a hidden layer in the end of other hidden layers
    Layer* new_layer;
    *new_layer = Layer(n_nodes);
    int n = hidden_layers.size();
    hidden_layers.push_back( new_layer); // adds new layer to vector of hidden layers
    new_layer->fully_connect(hidden_layers[n-1]);     // connects new layer to the last layer
}

void Network::add_layer(int i, int n_nodes, act_function f_activation){
    //adds a hidden layer in position i, with activation function, and number of nodes.
    Layer* new_layer; 
    *new_layer = Layer(n_nodes, f_activation);
    hidden_layers.insert(hidden_layers.begin() + i, new_layer);
    new_layer->fully_connect(hidden_layers[i-1]);
}