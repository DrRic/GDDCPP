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
            if(value<0){
                return 0.0;
            }
            return value; 
        }
        double divFunction(double value){
            if(value<0){
                return 0.0;
            }
            return 1; 
        }
};

int main(int argc, char **argv)
{
    double weightsArray_0_1[3][4] = {
        {-0.16595599,  0.91056768, -0.99977125, -0.90023925},
        {-0.70648822, -0.92794391, -0.62747958,  0.89703458},
        {-0.20646505, -0.03308324, -0.16161097,  0.00237016}
    }; 
    double weightsArray_1_2[4][1] = {
        {-0.5910955 },
        {1.13962134},
        {-0.94522481},
        {1.11023793}
    };
    
    double X[4][3] = {
        { 1, 0, 1 },
        { 0, 1, 1 },
        { 0, 0, 1 },
        { 1, 1, 1 } 
    };
    double y[4] = { 1, 1, 0, 0};
    
    int layers = 3;
    vector<int> nodesPerLayer {3,4,1};
    
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
        network[2].push_back(new Node(relufun));
        for(int j=0; j<nodesPerLayer[1]; j++){
            Weight* wp = new Weight(weightsArray_1_2[i][j]);
            network[2][i]->addWeightIn(wp);
            network[1][j]->addWeightOut(wp);
        }
    }


    
    // Populate the input layer with data
    for(int i=0; i<network[0].size(); i++){
        network[0][i]->setValue(X[i][0]);
        cout<< network[0][i]->getValue() <<"  ";
    }
    cout<<endl;
    
    
    // Feed foward the hidden and output layers
    for(int i=1;i<nodesPerLayer.size();i++){
        for(int j=0; j<network[i].size(); j++){
            network[i][j]->calcValue();
            cout<< network[i][j]->getValue() <<" ";
        }
        cout<<endl;
    }
     
    return 0;
     
}

