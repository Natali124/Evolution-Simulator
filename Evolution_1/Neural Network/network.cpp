#include "network.hpp"


void Network::propagate(){
    for (int i = 0; i < hidden_layer.size(); i++){
        hidden_layer[i].forward_propagate();
    }
    for (int i = 0; i < output_layer.size(); i++){
        output_layer[i].forward_propagate();
    }
}