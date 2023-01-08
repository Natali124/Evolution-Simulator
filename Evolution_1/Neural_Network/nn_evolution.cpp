#include "nn_evolution.hpp"
#include <fstream>
#include <QRandomGenerator>

// Comparison function to sort the vector elements
// by second element of tuples
bool sortbysec(tuple<Network*, double> a,
               tuple<Network*, double> b)
{
    return (get<1>(a) < get<1>(b));
}

vector<double> want_func(vector<double> in){
  // function that we want to emulate with the neural network
  return in;
}
double loss(vector<double> got, vector<double> expected){
  // get squared loss from expected output versus obtained output
  if(got.size() == expected.size()){
    double sum = 0;
    for(int i = 0; i < got.size(); i++){
      sum += pow(expected[i]-got[i],2);
      }
    //cout << sum << endl;
    return sum;
   }

}
double get_loss(Network* nn, vector<double> input, vector<double> expected){
  // get loss of a network for a given input and expected vector
  return loss(nn->propagate(input),expected);
}
vector<vector<double>> get_random_vectors(int n_vectors, int size_vectors){
  // generate n_vectors random vectors of size size_vectors
  vector<vector<double>> inputs = vector<vector<double>>(0);
  for (int i = 0; i < n_vectors; ++i) {
      vector<double> v_in = vector<double>(0);
      for (int j = 0; j < size_vectors; ++j) {
          v_in.push_back(QRandomGenerator::global()->generateDouble());
        }
      inputs.push_back(v_in);
    }
  return inputs;
}

double do_step(vector<Network*> &networks, int n, int tests,  double r, int n_in, int n_out){
  // Do one step of the evolution, return average loss

  // initializing network dictionary with loss
  vector<std::tuple<Network*, double>> network_loss = vector<std::tuple<Network*, double>>(0);
  for (Network* nn: networks) {
      network_loss.push_back(std::make_tuple(nn,0));
    }

  // initializing random inputs and expected outputs
  vector<vector<double>> inputs = get_random_vectors(tests,n_in);
  vector<vector<double>> expecteds = vector<vector<double>>(tests);
  for (int i = 0; i < tests; i++ ) {
    expecteds[i] = want_func(inputs[i]);
    }

  // getting loss for every test
  for (int i = 0; i < tests; i ++) {
      for (std::tuple<Network*, double> &t: network_loss) {
          Network* nn = std::get<0>(t); double old_loss = std::get<1>(t);
          double new_loss = get_loss(nn,inputs[i],expecteds[i]);
          std::get<1>(t) = old_loss + new_loss;
        }
    }

  // sort by loss in ascending order
  sort(network_loss.begin(),network_loss.end(),sortbysec);

  // average out the losses
  double avg_loss = 0;
  for (std::tuple<Network*, double> &t: network_loss) {
      double loss = std::get<1>(t);
      std::get<1>(t) = loss / tests;
      avg_loss += loss / tests;
    }
  avg_loss = (double) avg_loss / n;

  int n_keep = (int) n / r;
  vector<Network*> new_networks = vector<Network*>(0);


  // reproduce each of the first keep networks, each r times
  for (int i = 0; i < n_keep; i++) {
      Network* nn = std::get<0>(network_loss[i]);
      for(int j = 0; j<r; j++){
        new_networks.push_back(nn->reproduce());
        }

    }

  // Fill up in case it hasn't reached expected size yet
  int i = 0;
   while(new_networks.size() < n){
       Network* nn = std::get<0>(network_loss[i]);
       new_networks.push_back(nn->reproduce());
       i++;
     }
   networks = new_networks;

   return avg_loss;
}

void run_evolution(int n, double r, double tests, int n_in, int n_out, int n_gen, int print_every){
//  int n = 100; // number of networks
//  double r = 10; // number of children per network
//  double tests = 10; // number of test vectors per generation
//  int n_in = 5; // size of input vectors
//  int n_out = n_in; // size of output vectors (has to coincide with output of want_func!)
//  int n_gen = 1000; // number of generations
//  int print_every = 10; // prints average loss of generation every print_every-th generation
  vector<Network*> networks = vector<Network*>(0);
  for (int i = 0; i < n; ++i) {
      networks.push_back(new Network(n_in,n_out,2,7));
    }

  for (int gen = 0; gen < n_gen; ++gen) {
      double avg_loss = do_step(networks,n,tests,r,n_in,n_out);
      if(gen % print_every == 0){
      cout << "Generation " << gen << ": Avg. Loss = " << avg_loss << endl;
        }
    }
}


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

