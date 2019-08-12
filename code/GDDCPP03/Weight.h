

#ifndef WEIGHT_H
#define WEIGHT_H
class Weight;
#include "Node.h"

class Weight{
    
    private:
        double weight;
        Node* to;
        Node* from;
    public:
        static double alpha;
        Weight(double weight);
        double getWeight();
        void setTo(Node* to);
        void setFrom(Node* from);
        void updateWeight();
        double calcProduct();
        double calcError();
};
#endif
