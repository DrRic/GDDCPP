/*
 * Node.cpp
 * 
 * Copyright 2019 DR Ricardo Colasanti <ric@ric-CS-B>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


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

