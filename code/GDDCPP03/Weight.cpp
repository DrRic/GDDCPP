/*
 * Weight.cpp
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
    //cout<< this->from->getOutput()<<" "<< this->weight<<": ";
    return this->from->getOutput() * this->weight;
}

double Weight::calcError(){
    //cout<< this->from->getValue()<<" "<< this->weight<< endl;
    return this->to->getError() * this->weight;
}

void Weight::updateWeight(){
    //cout<< weight << endl;
    weight-= alpha * to->getError()*from->getOutput();
}
