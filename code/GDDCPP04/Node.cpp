#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(Actfun* actfun){
    this->value=0.0;
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

void Node::setValue(double value){
    this->value = value;
}

void Node::setError(double error){
    this->error = error;
}

void Node::setOutput(double output){
    this->output = output;
}

void Node::calcValue(){
    this->value = 0.0;
    for(int i=0; i<weightsIn.size(); ++i){
        this->value+=weightsIn[i]->calcProduct();
    } 
    output = actfun->actFunction(value);
}

void Node::calcError(){
    this->error = 0.0;
    for(int i=0; i<weightsOut.size(); ++i){
        this->error+=weightsOut[i]->calcError();
    } 
    error = error* actfun->divFunction(output);
}

void Node::backProp(){
    for(int i=0; i<weightsIn.size(); i++){
        weightsIn[i]->updateWeight();
    }
}

