
#ifndef NODE_H
#define NODE_H
class Node;
using namespace std;
#include "Weight.h"
#include "Actfun.h"
#include <vector>
class Node{
    private:
        double value,output,error;
        vector<Weight *> weightsIn,weightsOut;
        Actfun* actfun;
    public:
        Node(Actfun* actfun);
        void addWeightIn(Weight* wp);
        void addWeightOut(Weight* wp);
        void setValue(double value);
        double getValue();
        void calcValue();
};
#endif
