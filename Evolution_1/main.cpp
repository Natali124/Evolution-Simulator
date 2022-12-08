#include "Frontend/Windows/mainMenu.h"
#include "Neural_Network/network.hpp"
#include <QApplication>
#include <QGraphicsScene>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    Network n = Network();
    n.print_adj_list();
    return 0;
}
