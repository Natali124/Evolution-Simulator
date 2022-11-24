#include "layer.hpp"
#pragma once



class Network{ //network with 3 layers


// can you do a default constructor please? Cause I need one for Creature class (Garance)
public:
    void propagate();
    void get_output();
private:
    Layer input_layer;
    Layer output_layer;
    Layer hidden_layer;
};
