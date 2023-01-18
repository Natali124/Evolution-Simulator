#include "Frontend/environment_stats.h"
#include "environment.h"
#include "Frontend/Widgets/simulationView.h"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <QGraphicsScene>
#include "Neural_Network/nn_evolution.hpp"
#include <QRandomGenerator>


const double _my_size = 0.2;
vector<double> test_function(vector<double> in){
    // test function, assumes n_in to be 3 (size, can_eat_me, can_eat_it) and n_out to be 1 (>0.5 = move towards /  < 0.5 = move away)
    double size = in[0];
    double can_eat_me = in[1];
    double can_eat_it = in[2];
    //cout << "in: ["<< size << "," << can_eat_me << "," << can_eat_it << "]"<< endl;
    if(size == -1){
        return {-1};
      }
    if(can_eat_me > 0.5){
      if(can_eat_it > 0.5){
          return {double (_my_size > size)};
        } else {
          return {0};
        }
      } else {
        if(can_eat_it > 0.5){
            if(double (4*_my_size > size)){
                return {1};
              } else {
                return {-1};
              }
          } else {
            return {-1};
          }
      }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulationView menu(new Environment());
    SimulationView* menu_ptr = &menu;
    new Environment_Stats(menu_ptr);


    return a.exec();
}
