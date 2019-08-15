
#include "Weight.h"
#include <iostream>
double Weight::alpha = 0.2;  
using namespace std;
Weight::Weight(double weight){
    this->weight = weight;
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
    cout<< this->to->getError()<<"  " << this->weight<<endl;
    return this->to->getError() * this->weight;
}

void Weight::updateWeight(){
    weight-= alpha * to->getError()*from->getOutput();
}
