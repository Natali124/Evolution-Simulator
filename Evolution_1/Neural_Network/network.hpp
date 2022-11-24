#include "layer.hpp"
#pragma once



class Network{ //network with 3 layers
public:
    void propagate();
    void get_output();
private:
    Layer input_layer;
    Layer output_layer;
    Layer hidden_layer;
};