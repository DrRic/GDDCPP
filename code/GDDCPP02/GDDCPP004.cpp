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

class Sigfun: public Actfun{
    public:
        double actFunction(double value){
            return (1.0 / (1 + exp(-value))); 
        }
};

int main(int argc, char **argv)
{
    double weightsInArray[2][3][3] = {{{0.1, 0.2, -0.1},{-0.1,0.1, 0.9},{0.1, 0.4, 0.1}},
        {{0.3, 1.1, -0.3},{0.1, 0.2, 0.0},{0.0, 1.3, 0.1}}}; 
    double data[3][4] = {{8.5, 9.5, 9.9, 9.0},{0.65,0.8, 0.8, 0.9},{1.2, 1.3, 0.5, 1.0}};
    
    int layers = 3;
    vector<int> nodesPerLayer {3,3,3};
    
    Actfun* actfun = new Actfun();
    // Create first layer
    vector<vector<Node*>> network; 
    vector<Node*> v;
    network.push_back(v);
    for(int j=0; j<nodesPerLayer[0]; j++){
        network[0].push_back(new Node(actfun)); 
    }

    // Populate the hidden and ouput layers
    for(int layer=1;layer<nodesPerLayer.size();layer++){
        // create next layer
        vector<Node*> v;
        network.push_back(v);
        for(int i=0; i<nodesPerLayer[layer]; i++){
            network[layer].push_back(new Node(actfun));
            for(int j=0; j<nodesPerLayer[layer-1]; j++){
                Weight* wp = new Weight(weightsInArray[layer-1][i][j]);
                network[layer][i]->addWeightIn(wp);
                network[layer-1][j]->addWeightOut(wp);
            }
        }
    }
    
    // Populate the input layer with data
    for(int i=0; i<network[0].size(); i++){
        network[0][i]->setValue(data[i][0]);
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

