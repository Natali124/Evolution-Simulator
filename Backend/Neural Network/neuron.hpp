#include <vector>

class Neuron{
public:
    double get_value(){
        return value;
    }
    void forward_propagate(); //updates neuron based on neurons of the previous layer
    vector <Edge> input_edges;
private:
    double value;
    Layer layer;
};