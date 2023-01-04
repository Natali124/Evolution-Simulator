#include "network.hpp"
#include "layer.hpp"
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>

//using namespace std;

Network::Network(){
    // default constructor for Network. Assigns everything as nullptr
    input_layer = nullptr;
    output_layer = nullptr;
    hidden_layers = std::vector<Layer*>(0);
}

Network::Network(bool randomize){
    // simple constructor with input, output, and one hidden layer. Randomizes edges if randomize else all edges are 0.
    input_layer = new Layer(3);
    Layer* hid_layer = new Layer(3);
    output_layer = new Layer(3);
    std::vector<Layer*> v;
    v.push_back(hid_layer);
    hidden_layers = v;
    hid_layer->fully_connect(input_layer);
    output_layer->fully_connect(hid_layer);
    if (randomize){ randomize_edges(); }
}
Network::Network(int n_input, int n_output, int n_hidden_layers, int n_neurons_in_hidden){
    // Constructor with number of input, output, hidden layers, neurons in hidden_layers
    input_layer = new Layer(n_input);
    std::vector<Layer*> v = std::vector<Layer*>(0);
    for(int i = 0; i<n_hidden_layers; i++){
        v.push_back(new Layer(n_neurons_in_hidden));
        if (i==0){
            v[i]->fully_connect(input_layer);
          } else {
            v[i]->fully_connect(v[i-1]);
          }
      }
    hidden_layers = v;
    output_layer = new Layer(n_output);
    output_layer->fully_connect(v[v.size()-1]);
    randomize_edges();
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
std::vector <Layer*> Network::get_hidden_layers(){
    return hidden_layers;
}

int Network::size(){
  return hidden_layers.size() +2;
}
//setters:
void Network::set_input_layer(Layer* input_layer){
    this->input_layer = input_layer;
}
void Network::set_output_layer(Layer* output_layer){
    this->output_layer = output_layer;
}
void Network::set_hidden_layers(std::vector<Layer*> hidden_layers){
    this->hidden_layers = hidden_layers;
}


std::vector <double> Network::propagate(std::vector<double>v){
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

void Network::apply_on_all_edges(std::function<void(Edge&)> edge_function){
    // applies a function on all edges of network
    // function changes Edge object directly

    for(int j = +1; j < this->size(); j++){ // starts at 1, because input layer has no previous edges
        Layer* layer = (*this)[j];
        for(int i = 0; i< layer->size(); i++){
            Neuron* neuron = (*layer)[i];
            for(auto & edge : neuron->get_previous_edges()){
              edge_function(*edge);
            }
          }
    }
}

void Network::apply_on_all_weights(std::function<double(double)> weight_function){
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

Layer* Network::operator[](int i){
    if (i<0 or i> hidden_layers.size()+1){
        throw std::out_of_range ("Index out of range");
      }
     else if(i==0){
        return input_layer;
      } else if (1<= i and i<=hidden_layers.size()){
        return hidden_layers[i-1];
      } else {
      return output_layer;
      }
}

void copy_edge(Network* new_nn, Network* old_nn, Edge &e){
    // copies Edge e to new neural network of same size as the one before
    Neuron* n1 = e.get_start_neuron();
    Neuron* n2 = e.get_end_neuron();

    // get indeces of neurons in old network
    int i1; int j1; int i2; int j2;
    n1->get_full_index(old_nn,i1,j1);
    n2->get_full_index(old_nn,i2,j2);

    // find corresponding neurons in new network
    Neuron* new_n1 =(*((*new_nn)[i1]))[j1];
    Neuron* new_n2 =(*((*new_nn)[i2]))[j2];

    // create new edge
    Edge* new_e = new Edge(new_n1,new_n2);
    new_e->set_weight(e.get_weight());
    new_e->set_activation(e.get_activation());

    // add edge to the relevant neurons
    new_n1->add_edge(new_e,false);
    new_n2->add_edge(new_e, true);


}


Network* Network::copy(){
    // copies the network, creates a new Network object and copies all
    // connections and weights
    Network* n = new Network();

    // Adding Layers with appropriate number of neurons
    n->set_input_layer(new Layer(input_layer->get_neurons().size(),input_layer->get_activation_function()));
    n->set_output_layer(new Layer(output_layer->get_neurons().size(),output_layer->get_activation_function()));
    for (Layer* l : hidden_layers) {
        n->hidden_layers.push_back(new Layer(l->get_neurons().size(),l->get_activation_function()));
      }

    this->apply_on_all_edges([n, this](Edge& e){copy_edge(n,this,e);});

    return n;
}

void Network::print_adj_list(){

    std::vector<Neuron*> neurons =  input_layer->get_neurons();
    
    std::cout << "Input layer \n";

    for(auto& neuron: neurons){
        std::cout << neuron->get_id() << ": ";
        std::vector<Edge*> crnt_edges = neuron->get_next_edges();
        for(Edge* edge: crnt_edges){
            std::cout<<edge->get_end_neuron_id() << " ";}
        std::cout<<"\n";
    }

    
    int counter = 1;
    for(Layer* crnt_layer: hidden_layers){
        neurons = crnt_layer->get_neurons();

        std::cout << "Hidden layer "<< counter<< "\n";
        
        for(Neuron* neuron: neurons){

            std::cout << neuron->get_id() << ": ";
            std::vector<Edge*> crnt_edges = neuron->get_next_edges();
            for(Edge* edge: crnt_edges){
                std::cout<< edge->get_end_neuron_id() <<" ";}
            std::cout<<" \n";}
        counter += 1;}
     std::cout << "Done" << std::endl;}




void Network:: print_weights(){


    std::cout << "Input layer \n";

    input_layer->print_edges();
    std::cout << '\n';
    int counter = 1;
    for(Layer* crnt_layer: hidden_layers){

        std::cout << "Hidden layer "<< counter<< "\n";

        crnt_layer->print_edges();
        counter += 1;}

    std::cout << std::endl;
}

void Network:: print_values(){

    std::vector<Neuron*> neurons =  input_layer->get_neurons();

    std::cout << "Input layer \n";


    for(Neuron* neuron: neurons){
            std::cout << neuron->get_value()<< " " ;}

    std::cout << '\n';
    int counter = 1;
    for(Layer* crnt_layer: hidden_layers){
        neurons = crnt_layer->get_neurons();
        std::cout << "Hidden layer "<< counter<< "\n";

        for(Neuron* neuron: neurons){
         std::cout << neuron->get_value()<< " " ;
        }

        std::cout<<" \n";
        counter += 1;
      }

}

//Helper function for saving network

template <typename T> void vector_to_file(std::vector<std::vector<T>> inpt, std::string filename){
    /*Form of filename should be filename.txt (or pdf or however you want to save your file*/

        std::ofstream outfile (filename.c_str());

        for(std::vector<double> vect: inpt){
            for(double elm: vect){
                outfile << elm << " ";
            }
            outfile<<"\n";}}

void vector_to_file(std::vector<std::vector<double>> inpt, std::string filename){
/*Form of filename should be filename.txt (or pdf or however you want to save your file*/
    vector_to_file(inpt, filename);}


//Saving

std::vector<std::vector<double>> Network:: network_to_vector(){
    std::vector<std::vector<double>> output(0);
    output.push_back(input_layer->layer_to_vector());
    for(Layer* hidden: hidden_layers){
        output.push_back(hidden->layer_to_vector());}
     return output;}

void Network::network_to_file(std::string filename){
     std::vector<std::vector<double>> network_vect = this->network_to_vector();
     vector_to_file(network_vect, filename);}







