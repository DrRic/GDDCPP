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
        void init(int num_numbers, int *numbers,double dropout);
        double train( vector<double> *X, vector<double> *y);
        void feedFoward( vector<double> *X);
        int countCorrect( vector<double> *y);
        int getOutput();
        double rand_d();
};
#endif
