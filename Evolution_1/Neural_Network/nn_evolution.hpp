#pragma once
#include <tuple>
#include <vector>
#include <string>
using namespace std;
class Network;


bool sortbysec(tuple<Network*, double> a,
               tuple<Network*, double> b);

vector<double> want_func(vector<double> in);

double loss(vector<double> got, vector<double> expected);

double get_loss(Network* nn, vector<double> input, vector<double> expected);

vector<vector<double>> get_random_vectors(int n_vectors, int size_vectors);

double do_step(vector<Network*> &networks, int n, int tests,  double r, int n_in, int n_out);

void run_evolution(int n = 100, double r = 10, double tests = 10, int n_in = 5, int n_out = 5, int n_gen = 1000, int print_every = 10);

void run_evolution_in_file(int n, double r, double tests, int n_in, int n_out, int n_gen, int print_every, string filename);
