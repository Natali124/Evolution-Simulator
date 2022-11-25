#include "environment.h"
#include "living_being.h"

#include <cmath>


LivingBeing::LivingBeing(Coordinate position, float size) {
    type = none;
    this->size = size;
    this->position = position;
}

LivingBeing::LivingBeing(){
    type = none;
    size = 0;
    position = Coordinate();
}


std::vector<short> LivingBeing::See(int n, double d){
    std::vector<short> v; //Here we'll get all the output, It will be of size n

    for (int i=0; i<n; i++){
        v.push_back(this->See(n, i, d));
    }
    return v;
}

short LivingBeing::See(int n, int i, double d){
    // return a distance score with 256 meaning really close and 0 meaning nothing seen

    //start: x, y ; size = d/(2**k); teta = ((i+1)*pi)/(n+2), this will allow us to get the vision ray at good positions.
    short r=0;
    for (int k=0; k<8; k++){
        double size = d/(pow(2, k));
        if(need_function /*Something in the ray of size d and width Vision_ray_width, can't implement it now*/){
            //r==0=>nothing has been seen
            if (!r){
                r+=1;
            }
            // We use binary search to get the distance of the first seen object
            r+=pow(2, 8-k-1);
        }
    }
    return r;
}
