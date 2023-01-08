#include <vector>
#include <string>
#include <fstream>
#include "network.hpp"
using namespace std;
template<typename T> int find_index(std::vector<T> v, T el);

//Reconstructing network

vector<vector<double>> file_to_vector(string filename);

Layer vector_to_layer(vector<double> inpt);

Network vector_to_network(vector<vector<double>> inpt);

Network file_to_network(string filename);

