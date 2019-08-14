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

double Node::getError(){
    return error;
}
double Node::getValue(){
    return value;
}

double Node::getOutput(){
    return output;
}

void Node::calcValue(){
    this->value = 0.0;
    for(int i=0; i<weightsIn.size(); ++i){
        //cout<< "p["<<weightsIn[i]->calcProduct() <<"] ";    
        this->value+=weightsIn[i]->calcProduct();
    } 
    //cout<< "v["<<value<<"] " ; 
    output = actfun->actFunction(value);
}

void Node::calcError(){
    this->error = 0.0;
    for(int i=0; i<weightsOut.size(); ++i){
        //cout<< "p["<<weightsOut[i]->calcError() <<"] ";    
        this->error+=weightsOut[i]->calcError();
    } 
    //cout<< " e1["<<error<<"] " ; 
    error = error* actfun->divFunction(output);
}

void Node::backProp(){
    for(int i=0; i<weightsIn.size(); i++){
        weightsIn[i]->updateWeight();
        //cout<< weightsIn[i]->getWeight() << endl;
    }
}

