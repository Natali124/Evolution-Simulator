#include <vector>
#include "edge.hpp"


class Neuron{
public:

    // Constructors and destructur
    Neuron(int neuron_id, vector<Edge> previous_edges, Layer layer); //constructor for hidden/output layer
    Neuron(int neuron_id, vector<double> inputs, Layer layer); // constructor for input layer
    ~Neuron();


    // Getters
    double get_value();
    vector <Edge> get_previous_edges(); // returns input or previous edges 
    vector<double> get_inputs();
    vector <Edge> get_next_edges();

    // Setters
    void set_values();
   

    //Other functions  
    void forward_propagate(); //updates neuron based on neurons of the previous layer

private:
    int neuron_id;
   
    vector <Edge> previous_edges; //incomming edges
    vector <Edge> next_edges;  // output edges  
    vector <double> inputs (0);
    double value;  
    Layer layer;

};
