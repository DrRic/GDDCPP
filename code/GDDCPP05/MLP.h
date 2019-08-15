#ifndef MLP_H
#define MLP_H
class MLP;
using namespace std;
#include "Weight.h"
#include "Node.h"
#include "Actfun.h"
#include <vector>
class MLP{
    private:
        vector<vector<Node*>> network; 
        vector<Weight*> weights;
        int layers;    
    public:
        MLP();
        void init(int num_numbers, int *numbers);
        double train(int numX, double *X, int numy, double *y);
        double rand_d();
};
#endif
