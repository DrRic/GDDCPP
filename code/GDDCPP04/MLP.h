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
        int layers;    
    public:
        MLP(vector<int> nodesPerLayer,Actfun* relufun);
        void setInput(int indx,double value);
        double train(double *y);
        int getInputSize();
        double rand_d();
};
#endif
