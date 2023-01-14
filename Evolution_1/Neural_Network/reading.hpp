#include <fstream>
#include <vector>
#include <string>
#include "network.hpp"
#ifndef READING_HPP
#define READING_HPP



vector<vector<double>> file_to_vector(string filename);
Layer* vector_to_layer(vector<double> inpt);
Network* vector_to_network(vector<vector<double>> inpt);
Network* file_to_network(string filename);
#endif // READING_HPP
