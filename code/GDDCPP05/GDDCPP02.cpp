
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <math.h>  
#include "Node.h"
#include "Weight.h"
#include "Actfun.h"
#include "MLP.h"

using namespace std;


class Relufun: public Actfun{
    public:
        double actFunction(double value){
            if(value<=0){
                return 0.0;
            }
            return value; 
        }
        double divFunction(double value){
            if(value<=0){
                return 0.0;
            }
            return 1; 
        }
};





int main(int argc, char **argv){
    Weight::alpha = 0.2;
    MLP mlp = MLP({3,4,1},new Relufun());

    double X[4][3] = {
        { 1, 0, 1 },
        { 0, 1, 1 },
        { 0, 0, 1 },
        { 1, 1, 1 } 
    };
    double y[4][1] = { {1}, {1}, {0}, {0}};
    for(int it=0; it<60; it++){
        double er = 0;
        for(int k=0; k<4; k++){
            er += mlp.train(X[k],y[k]);
       }
       if(it % 10 == 0){
            cout<< er << endl;
       }
    }
    return 0; 
}

