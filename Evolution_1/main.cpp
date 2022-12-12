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

    Neuron neu = Neuron();
    neu.set_value(5);
    cout<<neu.get_value();

    cout<<"Before propagate \n";
    n.print_values();
    n.print_weights();

    n.propagate(vector<double>{1, 2, 3});

    cout<<"After propagate \n";
    n.print_values();
    n.print_weights();



    /*Neuron* n1 = new Neuron();
    Edge* e1 = new Edge(0);
    n1->add_edge(e1, true);

    cout<<n1->get_previous_edges().size();

    n1->remove_edge(0, true);

    cout<<n1->get_previous_edges().size();*/

    return 0;
}
