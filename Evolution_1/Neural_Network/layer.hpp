#include <cmath>


class Layer{
public:
    double f_activation(double x){ //default
    return 1/(pow(M_E, -x) + 1);
    }
};