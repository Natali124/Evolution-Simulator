#include "Frontend/Windows/mainMenu.h"
#include "Neural_Network/network.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    Neuron n1 = Neuron();
    Neuron n2 = Neuron();
    Edge e = Edge(&n1,&n2);
    Layer l1 = Layer(2);
    Layer l2 = Layer(3);
    Layer l3 = Layer(5);
    l2.fully_connect(&l1);
    l3.fully_connect(&l2);
    for (auto& n : l2.get_neurons()) {
        for(auto& e: n->get_previous_edges()){
            e->print();
          }
      }
    for (auto& n : l3.get_neurons()) {
        for(auto& e: n->get_previous_edges()){
            e->print();
          }
      }
    Network n = Network(false);
    n.print_adj_list();
    n.print_weights();

    n.add_layer(4);
    Layer* layer = n.get_hidden_layers()[1];
    for (auto& n : layer->get_neurons()) {
        for(auto& e: n->get_previous_edges()){
            e->print();
          }
      }

    n.print_adj_list();
    n.print_weights();


    return 0;
}
