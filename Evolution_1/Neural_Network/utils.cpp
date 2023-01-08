#include <fstream>
#include "utils.hpp"

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

Layer vector_to_layer(vector<double> inpt){
      int n_neurons = inpt.front();
      act_function func;
      if(inpt.back() == 0){
          func = Sigmoid;}
      else{
          func = ReLu;}
      Layer layer = Layer(n_neurons, func);
      return layer;}

Network vector_to_network(vector<vector<double>> inpt){
        Network network = Network();

        //Creating and connecting the layers
        Layer inpt_layer = vector_to_layer(inpt[0]);
        network.set_input_layer(&inpt_layer);
        vector<Layer> layers = {inpt_layer};

        vector<Layer*>hidden_layers(0);

        for(int i = 0; i < inpt.size()-1; i ++){
           Layer layer = vector_to_layer(inpt[i]);
           if(i == 0){
               layer.fully_connect(&inpt_layer);}
           else{
               layer.fully_connect(hidden_layers.back());}
           hidden_layers.push_back(&layer);
           layers.push_back(layer);}

        network.set_hidden_layers(hidden_layers);
        Layer otpt = Layer(inpt.back()[0]);
        network.set_output_layer(&otpt);
        layers.push_back(otpt);



        //Setting the edges


        for(int i = 0; i < inpt.size()-1; i ++){
            Layer crnt_layer = layers[i]; Layer next_layer = layers[i+1];
            vector<Neuron*> crnt_neurons = crnt_layer.get_neurons(); vector<Neuron*> next_neurons = next_layer.get_neurons();
            vector<double> weights_act = inpt[i];
            vector<Edge*> edges(0);
            for(int j = 0; j < inpt[i][0]; j +=2){
                Neuron* crnt_neuron = crnt_neurons[j];
                for(int k = 0; k < inpt[i+1][0]; k++ ){
                    Neuron* next_neuron = next_neurons[k];
                    Edge new_edge = Edge(weights_act[j+k+1]/100, crnt_neuron, next_neuron);
                    new_edge.set_activation(weights_act[j+k+2] == 0);
                    edges.push_back(&new_edge);
                  }
                crnt_neuron->set_next_edges(edges);}
            }
        return network;
        }

Network file_to_network(string filename){
        vector<vector<double>> net_vect = file_to_vector(filename);
        Network network = vector_to_network(net_vect);
        return network;
}


