#include "network.hpp"
#include <vector>
#include <functional>
using namespace std;


vector <double> Network::propagate(vector<double>v){
    // returns output vector for given input vector
    // going through the neural network

    input_layer.set_values(v);
    for (int i = 0; i < hidden_layers.size(); i++){
        for (int j = 0; j < hidden_layers[i].size(); j++){
            hidden_layers[i][j].forward_propagate();
        }
    }
    for (int i = 0; i < output_layer.size(); i++){
        output_layer[i].forward_propagate();
    }
    return output_layer.get_values();
}
void Network::apply_on_all_edges(function<void(Edge&)> edge_function){
    // applies a function on all edges of network
    // function changes Edge object directly

    // apply to all edges going to any hidden_layer
    for(auto & layer : hidden_layers){
        for(auto & neuron : layer.get_neurons()){
            for(auto & edge : neuron.get_previous_edges()){
              edge_function(edge);
            }
        }
    }
    // apply to all edges going to ouput_layer
    for(auto & neuron : output_layer.get_neurons()){
        for(auto & edge : neuron.get_previous_edges()){
            edge_function(edge);
          }
      }
}

void Network::apply_on_all_weights(function<double(double)> weight_function){
  // applies a function on all weights of the network
  apply_on_all_edges([weight_function](Edge& e) { e.set_weight(weight_function(e.get_weight())); });
}
