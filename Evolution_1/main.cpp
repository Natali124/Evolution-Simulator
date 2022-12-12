#include "Frontend/Windows/mainMenu.h"
#include "Neural_Network/network.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>


using namespace std;
double foo(double x){
  return x+0.4;
}
int main(int argc, char *argv[])
{

    Network* nn = new Network(false);
    Network n = *nn;
    n.print_adj_list();
    n.print_weights();

    n.add_layer(4);
    Layer* layer = n.get_hidden_layers()[1];
    for (auto& n : layer->get_neurons()) {
        for(auto& e: n->get_previous_edges()){
            e->print();
          }
      }
    n.randomize_edges();
    for (auto& n : layer->get_neurons()) {
        for(auto& e: n->get_previous_edges()){
            e->print();
          }
      }

    //n.print_adj_list();
    //n.print_weights();
    delete nn;
    return 0;
}
