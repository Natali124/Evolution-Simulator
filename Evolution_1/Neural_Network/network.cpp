#include "network.hpp"

void Network::propagate(){
    for (int i = 0; i < hidden_layers.size(); i++){
        hidden_layers[i].forward_propagate(); 
    }
    for (int i = 0; i < output_layer.size(); i++){
        output_layer[i].forward_propagate();
    }
}
