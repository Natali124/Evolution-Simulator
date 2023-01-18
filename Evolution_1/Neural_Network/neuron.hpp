#include <vector>
#include "edge.hpp"
#pragma once

using namespace std;

class Edge;
class Layer;
class Network;

class Neuron{
public:
    // Constructors and destructur
    Neuron();
    Neuron(vector<Edge*> previous_edges, Layer* parent_layer); //constructor for hidden/output layer
    Neuron(Layer* parent_layer); // constructor for input layer
    ~Neuron();


    // Getters
    double get_value();
    vector <Edge*> get_previous_edges(); // returns previous edges 
    vector <Edge*> get_next_edges();
    vector<double> get_next_weights();
    int get_id(); 
    int get_index(); // returns index of neuron in parent_layer
    void get_full_index(Network* n, int& i, int& j); // sets (i,j) where i is index of parent layer in network, j is index of neuron in parent layer

    // Setters
    void set_value(double value);
    void set_next_edges(vector<Edge*> edges);// Did not implement this functions, was not sure how to do it
    void set_previous_edges(vector<Edge*> edges);
   
    //Other functions  
    void forward_propagate(); //updates neuron based on neurons of the previous layer
    void add_edge(Edge* edge, bool previous); // adds an edge. boolean previous indicates wether its in next_edges or previous_edges
    void remove_edge(int index, bool previous); // removes edge at given index, previous indicates if it is in previous_edges or next_edges. removes edge from both of the connected neurons
    void remove_edge(Edge* edge, bool previous); //removes given edge found in previous_edges or next_edges as indicated by previous. removes edge from only this neuron
    bool is_connected(Neuron*);

private:
    static int neuron_counter; //Number of existing neiurons. Increases everytime a neuron is intialized, decreases when a neuron is destroyed
    int neuron_id; // ID or name of the neuron
    vector <Edge*> previous_edges; //incomming edges
    vector <Edge*> next_edges;  // output edges  
    double value;
    Layer* parent_layer;

};
