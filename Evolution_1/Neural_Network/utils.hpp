#include "network.hpp"
#include <vector>

template<typename T> int find_index(std::vector<T> v, T el){
  // returns index of element in vector. returns -1 if element not in vector.
  auto a = v.begin();
  auto b = v.end();
  int i = find(a,b,el) - a;
  if (i!= v.size()){
      return i;
    } else {
      return -1;
    }
}

//Reconstructing network

vector<vector<double>> file_to_vector(string filename);

Layer vector_to_layer(vector<double> inpt);

Network vector_to_network(vector<vector<double>> inpt);

Network file_to_network(string filename);
