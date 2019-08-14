#include "Weight.h"
#include <iostream>
double Weight::alpha = 0.2;  
using namespace std;
Weight::Weight(double value){
    this->weight = value;
}

double Weight::getWeight(){
    return weight;
}

void Weight::setTo(Node* to){
    this->to = to;
}
void Weight::setFrom(Node* from){
    this->from = from;
}
double Weight::calcProduct(){
    return this->from->getOutput() * this->weight;
}

double Weight::calcError(){
    return this->to->getError() * this->weight;
}

void Weight::updateWeight(){
    weight-= alpha * to->getError()*from->getOutput();
}
