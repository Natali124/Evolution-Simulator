#include <vector>
#include "edge.hpp"
#pragma once

using namespace std;

class Edge;
class Layer;

class Neuron{
public:

    // Constructors and destructur
    Neuron();
    Neuron( vector<Edge*> previous_edges, Layer* parent_layer); //constructor for hidden/output layer
    Neuron( Layer* parent_layer); // constructor for input layer
    ~Neuron();


    // Getters
    double get_value();
    vector <Edge*> get_previous_edges(); // returns previous edges 
    vector <Edge*> get_next_edges();

    // Setters
    void set_value(double value);
    void set_next_edges(vector<Edge> edges);// Did not implement this functions, was not sure how to do it
    void set_previous_edges(vector<Edge> edges);
   
    //Other functions  
    void forward_propagate(); //updates neuron based on neurons of the previous layer
    void add_edge(Edge* edge, bool previous); // adds an edge. boolean previous indicates wether its in next_edges or previous_edges
    void reomve_edge(Edge* edge); // removes edge connecting neurn to other_neuron


private:
    static int neuron_counter;
    vector <Edge*> previous_edges; //incomming edges
    vector <Edge*> next_edges;  // output edges  
    double value;  
    Layer* parent_layer;

};
