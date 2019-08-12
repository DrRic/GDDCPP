

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
        Weight(double weight);
        void setTo(Node* to);
        void setFrom(Node* from);
        double getProduct();
};
#endif
