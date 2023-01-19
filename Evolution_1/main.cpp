#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include "Neural_Network/reading.hpp"
#include "Neural_NetworK/nn_evolution.hpp"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <mainwindow.h>
#include <fstream>
//#include <stdio.h>
//#include <conio.h>
//#include <Python.h>


int main(int argc, char *argv[])
{
    //void run_evolution(int n, double r, double tests, int n_in, int n_out, int n_gen, int print_every)
    //  int n = 100; // number of networks
    //  double r = 10; // number of children per network
    //  double tests = 10; // number of test vectors per generation
    //  int n_in = 5; // size of input vectors
    //  int n_out = n_in; // size of output vectors (has to coincide with output of want_func!)
    //  int n_gen = 1000; // number of generations
    //  int print_every = 10; // prints average loss of generation every print_every-th generation

    run_evolution_in_file(10, 10, 10, 5, 5, 10, 10, "Users\natal\Documents\GitHub\Evolution-Simulator\Evolution_1\results1.txt");
    return 0;
}
