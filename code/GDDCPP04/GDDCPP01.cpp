/*
 * Test.cpp
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

#include <iostream>
#include <math.h>  
#include "Node.h"
#include "Weight.h"
#include "Actfun.h"

using namespace std;


class Relufun: public Actfun{
    public:
        double actFunction(double value){
            if(value<=0){
                return 0.0;
            }
            return value; 
        }
        double divFunction(double value){
            if(value<=0){
                return 0.0;
            }
            return 1; 
        }
};

int main(int argc, char **argv)
{
    Weight::alpha = 0.2;
    double weightsArray_0_1[3][3] = {
        {-0.16595599,  -0.39533485, -0.62747958},
        {0.44064899, -0.70648822, -0.30887855},
        {-0.99977125, -0.81532281, -0.20646505}
    }; 
    double weightsArray_1_2[3][1] = {
        {0.07763347 },
        {-0.16161097},
        {0.370439}
    };
    
    double X[4][3] = {
        { 1, 0, 1 },
        { 0, 1, 1 },
        { 0, 0, 1 },
        { 1, 1, 1 } 
    };
    double y[4] = { 1, 1, 0, 0};
    
    int layers = 3;
    vector<int> nodesPerLayer {3,3,1};
    
    Actfun* actfun = new Actfun();
    Actfun* relufun = new Relufun();
    // Create first layer
    vector<vector<Node*>> network; 
    vector<Node*> v1;
    network.push_back(v1);
    for(int j=0; j<nodesPerLayer[0]; j++){
        network[0].push_back(new Node(actfun)); 
    }

    // Create the hiden layer
    vector<Node*> v2;
    network.push_back(v2);
    for(int i=0; i<nodesPerLayer[1]; i++){
        network[1].push_back(new Node(relufun));
        for(int j=0; j<nodesPerLayer[0]; j++){
            Weight* wp = new Weight(weightsArray_0_1[i][j]);
            network[1][i]->addWeightIn(wp);
            network[0][j]->addWeightOut(wp);
        }
    }
        
    // Create the output layer
    vector<Node*> v3;
    network.push_back(v3);
    for(int i=0; i<nodesPerLayer[2]; i++){
        network[2].push_back(new Node(actfun));
        for(int j=0; j<nodesPerLayer[1]; j++){
            Weight* wp = new Weight(weightsArray_1_2[i][j]);
            network[2][i]->addWeightIn(wp);
            network[1][j]->addWeightOut(wp);
        }
    }


    
    // Populate the input layer with data
    for(int i=0; i<network[0].size(); i++){
        network[0][i]->setOutput(X[0][i]);
        cout<< network[0][i]->getOutput() <<"  ";
    }
    cout<<endl;
    
    // hidden layer
    for(int j=0; j<network[1].size(); j++){
        network[1][j]->calcValue();
        cout<< network[1][j]->getOutput() <<endl;
    }
    cout<<endl;

    // output layer
    for(int j=0; j<network[2].size(); j++){
        network[2][j]->calcValue();
        cout<< network[2][j]->getOutput() <<endl;
    }
    cout<<endl;

    // calculate the ouput error
    for(int j=0; j<network[2].size(); j++){
        network[2][j]->setError(network[2][j]->getOutput()-y[0]);
        cout<<network[2][j]->getError() <<endl;
    }
    cout<<endl;

    // calculate the hidden error
    for(int j=0; j<network[1].size(); j++){
        network[1][j]->calcError();
        cout<< network[1][j]->getError() <<endl;
    }
    cout<<endl;

    // backprop the ouput error
    for(int j=0; j<network[2].size(); j++){
        network[2][j]->backProp();
    }
    cout<<endl;
    
     // backprop the hidden error
    for(int j=0; j<network[1].size(); j++){
        network[1][j]->backProp();
    }
    cout<<endl;
    return 0;
     
}

