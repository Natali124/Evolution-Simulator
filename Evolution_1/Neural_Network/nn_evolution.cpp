#include "nn_evolution.hpp"
#include "network.hpp"
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
   } else {
      throw std::invalid_argument("Vectors don't have the same size!");
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

double do_step(vector<Network*> &networks, int n, int tests,  double r, int n_in, int n_out, bool save_networks, string safe_path, int crnt_gen){
  // Do one step of the evolution, return average loss#

  // bool save_networks = false; // whether to save best, medium and worst network
  // string safe_path = ""; // where to save the networks
  // int crnt_gen = 0; // current generation, only used for storing of networks

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

  if(save_networks){
    Network* best_nn =  std::get<0>(network_loss[0]);
    Network* medium_nn =  std::get<0>(network_loss[(int) (n-1)/2]);
    Network* worst_nn = std::get<0>(network_loss[n-1]);
    cout << "Saving networks" << endl;
    best_nn->network_to_file(safe_path + "gen" + to_string(crnt_gen) +"_best.txt");
    medium_nn->network_to_file(safe_path + "gen" + to_string(crnt_gen) + "_medium.txt");
    worst_nn->network_to_file(safe_path + "gen" + to_string(crnt_gen) +"_worst.txt");
   }

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

double do_step(vector<Network*> &networks, int n, int tests,  double r, int n_in, int n_out){
  return do_step(networks,n,tests,r,n_in,n_out,false,"",0);
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
      networks.push_back(new Network(n_in,n_out,1,n_in));
    }

  for (int gen = 0; gen < n_gen; ++gen) {
      double avg_loss = do_step(networks,n,tests,r,n_in,n_out);
      if(gen % print_every == 0){
      cout << "Generation " << gen << ": Avg. Loss = " << avg_loss << endl;
        }
    }
}



void run_evolution_in_file(int n, double r, double tests, int n_in, int n_out, int n_gen, int print_every, string filename, bool save_networks, string save_path){
//  int n = 100; // number of networks
//  double r = 10; // number of children per network
//  double tests = 10; // number of test vectors per generation
//  int n_in = 5; // size of input vectors
//  int n_out = n_in; // size of output vectors (has to coincide with output of want_func!)
//  int n_gen = 1000; // number of generations
//  int print_every = 10; // saves average loss of generation every print_every-th generation
  //  string filename; // saves averages losses to filename
  //  bool save_networks; // bool wether to save the best / medium/ worst networks of first and last generation
  // string save_path; path to where the networks should be saved
  ofstream outfile (filename.c_str());
  cout << "Writing: "<< filename <<endl;
  outfile << n << endl << r << endl << tests << endl << n_in << endl << n_out <<endl << n_gen << endl << print_every <<endl;
  vector<Network*> networks = vector<Network*>(0);
  for (int i = 0; i < n; ++i) {
      networks.push_back(new Network(n_in,n_out,1,n_in));
    }
  for (int gen = 0; gen < n_gen; ++gen) {
      double avg_loss = do_step(networks,n,tests,r,n_in,n_out,save_networks && gen%(n_gen-1)==0,save_path,gen);
      if(gen % print_every == 0){
      outfile << "Generation: " << gen << " Avg.Loss: " << avg_loss << endl;
        }
    }
  cout << "Finished!" << endl;

}
void run_evolution_in_file(int n, double r, double tests, int n_in, int n_out, int n_gen, int print_every, string filename){
  run_evolution_in_file(n,r,tests,n_in,n_out,n_gen,print_every,filename,false,"");
}
