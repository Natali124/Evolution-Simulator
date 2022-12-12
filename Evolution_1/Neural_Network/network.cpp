#include "network.hpp"
#include "layer.hpp"
#include <vector>
#include <functional>
#include <iostream>
using namespace std;


Network::Network(bool randomize){
    // default constructor with default input, output, and one hidden layer. Randomizes edges.
    input_layer = new Layer(3);
    Layer* hid_layer = new Layer(3);
    output_layer = new Layer(3);
    vector<Layer*> v;
    v.push_back(hid_layer);
    hidden_layers = v;
    hid_layer->fully_connect(input_layer);
    output_layer->fully_connect(hid_layer);
    if (randomize){ randomize_edges(); }
}

Network::~Network(){
    // Deletes all layers
    delete input_layer;
    delete output_layer;
    for(auto& layer:hidden_layers){
        delete layer;
      }
}

//getters:
Layer* Network::get_input_layer(){
    return input_layer;
}
Layer* Network::get_output_layer(){
    return output_layer;
}
vector <Layer*> Network::get_hidden_layers(){
    return hidden_layers;
}

//setters:
void Network::set_input_layer(Layer* input_layer){
    this->input_layer = input_layer;
}
void Network::set_output_layer(Layer* output_layer){
    this->output_layer = output_layer;
}
void Network::set_hidden_layers(vector<Layer*> hidden_layers){
    this->hidden_layers = hidden_layers;
}


vector <double> Network::propagate(vector<double>v){
    // returns output vector for given input vector
    // going through the neural network

    input_layer->set_values(v);
    for (int i = 0; i < hidden_layers.size(); i++){
        for (int j = 0; j < hidden_layers[i]->size(); j++){
            (*(hidden_layers[i]))[j]->forward_propagate();
        }
    }
    for (int i = 0; i < output_layer->size(); i++){
        ((*output_layer)[i])->forward_propagate();
    }
    return (*output_layer).get_values();
}

void Network::randomize_edges(){
    //for each edge call randomize edge.

    // apply to all edges going to any hidden_layer
    for(auto & layer : hidden_layers){
        for(auto & neuron : layer->get_neurons()){
            for(auto & edge : neuron->get_previous_edges()){
              edge->randomize_weight();
            }
        }
    }
    // apply to all edges going to ouput_layer
    for(auto & neuron : output_layer->get_neurons()){
        for(auto & edge : neuron->get_previous_edges()){
            edge->randomize_weight();
          }
      }
}

void Network::apply_on_all_edges(function<void(Edge&)> edge_function){
    // applies a function on all edges of network
    // function changes Edge object directly

    // apply to all edges going to any hidden_layer
    for(auto & layer : hidden_layers){
        for(auto & neuron : layer->get_neurons()){
            for(auto & edge : neuron->get_previous_edges()){
              edge_function(*edge);
            }
        }
    }
    // apply to all edges going to ouput_layer
    for(auto & neuron : output_layer->get_neurons()){
        for(auto & edge : neuron->get_previous_edges()){
            edge_function(*edge);
          }
      }
}

void Network::apply_on_all_weights(function<double(double)> weight_function){
  // applies a function on all weights of the network
  apply_on_all_edges([weight_function](Edge& e) { e.set_weight(weight_function(e.get_weight())); });
}

void Network::remove_layer(){
    //removes the last layer from hidden layers
    hidden_layers.pop_back();
}

void Network::add_layer(int n_nodes){
    //adds a hidden layer in the end of other hidden layers
    Layer* new_layer = new Layer(n_nodes);
    int n = hidden_layers.size();

    hidden_layers[n-1]->disconnect(false);   //disconnect last layer to next layer
    new_layer->fully_connect(hidden_layers[n-1]);     // connects new layer to the last layer
    output_layer->fully_connect(new_layer);
    hidden_layers.push_back(new_layer); // adds new layer to vector of hidden layers

}

void Network::add_layer(int i, int n_nodes, act_function f_activation){
    //adds a hidden layer in position i, with activation function, and number of nodes.
    Layer* new_layer = new Layer(n_nodes, f_activation);
    hidden_layers.insert(hidden_layers.begin() + i, new_layer);

    //dissconnet layer at position i-1 or input layer to layer at position i and connect to new layer
    if(i == 0){
      input_layer->disconnect(false);
      new_layer->fully_connect(input_layer);}
    else{
    hidden_layers[i-1]->disconnect(false);
    new_layer->fully_connect(hidden_layers[i-1]);}

    //connect layer at position i to the new layer
    hidden_layers[i+1]->fully_connect(new_layer);

    new_layer->set_activation_function(f_activation);

}

Network Network::copy(){
    //copies the network so that children start with parents' networks
    //WARNING: I am not sure this implementation works correctly, we might need to add copy function to layers/nodes
    //WARNING2: Since we work with pointers, it definitely doesn't work and we need to find some other mechanism
    Network new_network = Network();
    new_network.input_layer = this->input_layer;
    new_network.output_layer = this->output_layer;
    new_network.hidden_layers = this->hidden_layers;
    return new_network;
}

void Network::print_adj_list(){

    vector<Neuron*> neurons =  input_layer->get_neurons();
    
    cout << "Input layer \n";

    for(auto& neuron: neurons){
        vector<Edge*> crnt_edges = neuron->get_next_edges();    
        for(Edge* edge: crnt_edges){
            cout<<edge->get_end_neuron_id() << " ";}
        cout<<"\n";
    }

    
    int counter = 1;
    for(Layer* crnt_layer: hidden_layers){
        neurons = crnt_layer->get_neurons();

        cout << "Hidden layer "<< counter<< "\n";
        
        for(Neuron* neuron: neurons){
            vector<Edge*> crnt_edges = neuron->get_next_edges();
            for(Edge* edge: crnt_edges){
                cout<< edge->get_end_neuron_id() <<" ";}
            cout<<" \n";}
        counter += 1;}
     cout << "Done" << std::endl;}




void Network:: print_weights(){

    vector<Neuron*> neurons =  input_layer->get_neurons();
    
    cout << "Input layer \n";

    
    for(Neuron* neuron: neurons){
        for(double weight: neuron->get_next_weights()){
            cout << weight<< " " ;
        }
         cout << '\n';
    }
    cout << '\n';
    int counter = 1;
    for(Layer* crnt_layer: hidden_layers){
        neurons = crnt_layer->get_neurons();

        cout << "Hidden layer "<< counter<< "\n";
        
        for(Neuron* neuron: neurons){
         for(double weight: neuron->get_next_weights()){
            cout << weight<< " " ;
        }
        
        cout<<" \n";}
        counter += 1;}}

void Network:: print_values(){

    vector<Neuron*> neurons =  input_layer->get_neurons();

    cout << "Input layer \n";


    for(Neuron* neuron: neurons){
            cout << neuron->get_value()<< " " ;}

    cout << '\n';
    int counter = 1;
    for(Layer* crnt_layer: hidden_layers){
        neurons = crnt_layer->get_neurons();
        cout << "Hidden layer "<< counter<< "\n";

        for(Neuron* neuron: neurons){
         cout << neuron->get_value()<< " " ;
        }

        cout<<" \n";}
        counter += 1;}


