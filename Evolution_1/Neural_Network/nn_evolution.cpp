#include "nn_evolution.hpp"
#include "network.hpp"
#include <QRandomGenerator>
#include <functional>

// Comparison function to sort the vector elements
// by second element of tuples
bool sortbysec(tuple<Network*, double> a,
               tuple<Network*, double> b)
{
    return (get<1>(a) < get<1>(b));
}

vector<double> want_func(vector<double> in){
  // default function that the network is supposed to replicate
  return in;
}
double loss(vector<double> got, vector<double> expected){
  // get squared loss from expected output versus obtained output
  if(got.size() == expected.size()){
    double sum = 0;
    for(int i = 0; i < got.size(); i++){
        if(expected[i]!= -1){
           // -1 if value is not important / 0 loss
          sum += pow(expected[i]-got[i],2);
        }
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

double do_step(vector<Network*> &networks, int n, int tests,  double r, int n_in, int n_out, function<vector<double>(vector<double>)> test_function){
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
    expecteds[i] = test_function(inputs[i]);
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

void run_evolution(int n, double r, double tests, int n_in, int n_out, int n_gen, int print_every, int n_hidden_layers, int n_neurons_in_hidden, std::function<vector<double>(vector<double>)> test_function){
//  int n = 100; // number of networks
//  double r = 10; // number of children per network
//  double tests = 10; // number of test vectors per generation
//  int n_in = 5; // size of input vectors
//  int n_out = n_in; // size of output vectors (has to coincide with output of want_func!)
//  int n_gen = 1000; // number of generations
//  int print_every = 10; // prints average loss of generation every print_every-th generation
//  int n_hidden_layers = 1; // number of hidden layers in network
//  int n_neurons_in_hidden = 5; //number of neurons in each hidden layer
//  std::function<vector<double>(vector<double>)> test_function // test (goal) function -> has to take input of size n_in and give output of size n_out, puts -1 in output neurons if value can be arbitrary

  // Check if function works with correct arguments:
  vector<vector<double>> test_vectors = get_random_vectors(10,n_in);
  for (vector<double> vector : test_vectors) {
      try {
        std::vector<double> out = test_function(vector);
        if(out.size() != n_out){
          std::cout << "test_function gives output of size " << out.size() << " instead of expected size " << n_out<< std::endl;
          throw std::invalid_argument("test_function gives output of size: " + to_string(out.size()) + " instead of expected size: " + to_string(n_out));
          }
      } catch (...) {
          throw std::invalid_argument("test_function does not compile or has incorrect output size");;
      }

    }

  // initialize n random networks
  vector<Network*> networks = vector<Network*>(0);
  for (int i = 0; i < n; ++i) {
      networks.push_back(new Network(n_in,n_out,n_hidden_layers,n_neurons_in_hidden));
    }

  // run evolution
  for (int gen = 0; gen < n_gen; ++gen) {
      double avg_loss = do_step(networks,n,tests,r,n_in,n_out, test_function);
      if(gen % print_every == 0){
      cout << "Generation " << gen << ": Avg. Loss = " << avg_loss << endl;
        }
    }
}
