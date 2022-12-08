#include "Frontend/Windows/mainMenu.h"
#include "Neural_Network/network.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    Edge e1 = Edge();
    Edge e2 = Edge();
    Edge e3 = Edge();
    Edge e4 = Edge();
    vector<Edge*> v;
    v.push_back(&e1);
    v.push_back(&e2);
    v.push_back(&e3);
    v.push_back(&e4);

    Layer l = Layer();
    Neuron n = Neuron(v, &l);
    auto pnt = &e2;
    n.remove_edge(pnt);
    vector<Edge*>ve = n.get_previous_edges();
    for (int i = 0; i < ve.size(); i++){
        ve[i]->randomize_weight(); //problem with this
    }
    for (int i = 0; i < ve.size(); i++){
        cout << (ve[i]->get_weight()) << endl;
    }
}
