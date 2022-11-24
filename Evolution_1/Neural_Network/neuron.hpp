#include <vector>
#include "edge.hpp"
#pragma once

using namespace std;

class Edge;
class Layer;

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
    void set_next_edges(); // Did not implement this functions, was not sure how to do it
   

    //Other functions  
    void forward_propagate(); //updates neuron based on neurons of the previous layer
    void add_edge(Edge edge, bool previous); // adds an edge. boolean previous indicates wether its in next_edges or previous_edges
    void reomve_edge(Edge edge); // removes edge connecting neurn to other_neuron


private:
    int neuron_id;
    vector <Edge> previous_edges; //incomming edges
    vector <Edge> next_edges;  // output edges  
    vector <double> inputs;
    double value;  
    Layer layer;

};