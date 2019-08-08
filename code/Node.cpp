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

Node::Node(){
    this->value=0.0;
    this->output=0.0;
    this->error=0.0;
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

double Node::getValue(){
    return value;
}

void Node::calcValue(){
    this->value = 0.0;
    for(int i=0; i<weightsIn.size(); ++i){
        this->value+=weightsIn[i]->getProduct();
    } 
}

