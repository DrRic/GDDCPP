#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(Actfun* actfun){
    this->output=0.0;
    this->error=0.0;
    this->actfun = actfun;
}

void Node::addWeightIn(Weight* wp){
    wp->setTo(this);
    this->weightsIn.push_back(wp);
}

void Node::addWeightOut(Weight* wp){
    wp->setFrom(this);
    this->weightsOut.push_back(wp);
}

void Node::setError(double error){
    this->error = error;
}

void Node::setOutput(double output){
    this->output = output;
}

void Node::calcValue(){
    double value = 0.0;
    for(int i=0; i<weightsIn.size(); ++i){
        value+=weightsIn[i]->calcProduct();
    } 
    output = actfun->actFunction(value);
}

void Node::calcError(){
    double err = 0.0;
    for(int i=0; i<weightsOut.size(); ++i){
        err+=weightsOut[i]->calcError();
    } 
    this->error = err* actfun->divFunction(output);
}


