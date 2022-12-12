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
    Network* nn2 = new Network(4,3,1,2);
    nn2->print_weights();
    nn2->randomize_edges();

    nn2->print_weights();
    vector<double> in = {0,1,2,3};
    vector<double> v = nn2->propagate(in);

    //nn2->print_adj_list();
    return 0;
}
