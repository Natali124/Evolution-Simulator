#include "network.hpp"
#include <vector>
using namespace std;

vector <double> Network::propagate(vector<double>v){
    input_layer.set_values(v);
    for (int i = 0; i < hidden_layers.size(); i++){
        for (int j = 0; j < hidden_layers[i].size(); j++){
            hidden_layers[i][j].forward_propagate();
        }
    }
    for (int i = 0; i < output_layer.size(); i++){
        output_layer[i].forward_propagate();
    }
}