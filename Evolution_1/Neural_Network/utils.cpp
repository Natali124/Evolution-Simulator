#include <fstream>
#include "utils.hpp"



/*void vector_to_file(vector<vector<double>> inpt, string filename){
/*Form of filename should be filename.txt (or pdf or however you want to save your file)
    vector_to_file(inpt, filename);}*/


//Reconstructing the network form file

//Reading file

vector<vector<double>> file_to_vector(string filename){
    char space[] = " ";

    ifstream inpt_file;
    inpt_file.open(filename);
    string line;

    vector<vector<double>> output(0);

    while(getline(inpt_file, line)){
        int prev_space = 0;
        int n = line.size();
        vector<double> crnt_line(0);
        for(int i = 0; i < n-1; i++){
            char elm = line[i];
            if(elm == *space){
               int number = stoi(line.substr(prev_space, i-prev_space));
               crnt_line.push_back(number);
               prev_space = i+1;}}
        int number = stoi(line.substr(prev_space));
        crnt_line.push_back(number);
        output.push_back(crnt_line);
       }
        return output;}

//Constructing netowrk from file

Layer* vector_to_layer(vector<double> inpt){
      int n_neurons = inpt.front();
      act_function func;
      if(inpt.back() == 0){
          func = Sigmoid;}
      else{
          func = ReLu;}
      Layer* layer = new Layer(n_neurons, func);
      return layer;}

Network* vector_to_network(vector<vector<double>> inpt){
        Network* network = new Network();

        //Creating and connecting the layers
        Layer* inpt_layer = vector_to_layer(inpt[0]);
        network->set_input_layer(inpt_layer);
        vector<Layer*> layers = {inpt_layer};

        vector<Layer*>hidden_layers(0);

        for(int i = 1; i < inpt.size()-1; i ++){
           Layer* layer = vector_to_layer(inpt[i]);
           hidden_layers.push_back(layer);
           layers.push_back(layer);}

        network->set_hidden_layers(hidden_layers);
        Layer* otpt = new Layer(inpt.back()[0]);
        network->set_output_layer(otpt);
        layers.push_back(otpt);



        //Setting the edges


        for(int i = 0; i < inpt.size()-1; i ++){
            Layer* crnt_layer = layers[i]; Layer* next_layer = layers[i+1];
            vector<Neuron*> crnt_neurons = crnt_layer->get_neurons(); vector<Neuron*> next_neurons = next_layer->get_neurons();
            vector<double> weights_act = inpt[i];

            for(int j = 0; j < inpt[i][0]+1 ; j ++){
                Neuron* crnt_neuron;
                if(j < inpt[i][0]){
                    crnt_neuron = crnt_neurons[j];}
                else {
                    crnt_neuron = crnt_layer->get_bias_neuron();}

                vector<Edge*> edges(0);
                int n = inpt[i+1][0];
                for(int k = 0; k < n; k++ ){
                    Neuron* next_neuron = next_neurons[k];
                    Edge* new_edge = new Edge(weights_act[2*(n*j+k)+1]/100, crnt_neuron, next_neuron);
                    new_edge->set_activation(weights_act[2*(n*j+k)+2] == 0);
                    edges.push_back(new_edge);
                    next_neuron->add_edge(new_edge,true);
                  }
                crnt_neuron->set_next_edges(edges);}
            }
        return network;
        }

Network* file_to_network(string filename){
        vector<vector<double>> net_vect = file_to_vector(filename);
        Network* network = vector_to_network(net_vect);
        return network;
}


