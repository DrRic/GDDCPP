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
#include "Node.h"

#define NODESIN 3
#define NODESHIDDEN1 3
#define NODESOUT 3
using namespace std;

int main(int argc, char **argv)
{
    /*
                 #toes %win #fans
ih_wgt = [ [0.1, 0.2, -0.1], #hid[0]
           [-0.1,0.1, 0.9], #hid[1]
           [0.1, 0.4, 0.1] ] #hid[2]

           #hid[0] hid[1] hid[2]
hp_wgt = [ [0.3, 1.1, -0.3], #hurt?
           [0.1, 0.2, 0.0], #win?
           [0.0, 1.3, 0.1] ] #sad?
     */
    double weightsInArray[3][3] = {{0.1, 0.2, -0.1},{-0.1,0.1, 0.9},{0.1, 0.4, 0.1}}; 
    double weightsHiddenArray[3][3] = {{0.3, 1.1, -0.3},{0.1, 0.2, 0.0},{0.0, 1.3, 0.1}}; 
    
  
    double data[3][4] = {{8.5, 9.5, 9.9, 9.0},{0.65,0.8, 0.8, 0.9},{1.2, 1.3, 0.5, 1.0}};
    
   
    
    Node* layerIn[NODESIN];
    Node* layerHidden[NODESHIDDEN1];
    Node* layerOut[NODESOUT];
    

    for(int i=0; i<NODESHIDDEN1; i++){
        layerHidden[i] = new Node();
        for(int j=0; j<NODESIN; j++){
            if(i==0){
               layerIn[j] = new Node(); 
            }
            Weight* wp = new Weight(weightsInArray[i][j]);
            layerHidden[i]->addWeightIn(wp);
            layerIn[j]->addWeightOut(wp);
        }
    }
    
    for(int i =0; i<NODESOUT; i++){
        layerOut[i] = new Node();
        for(int j=0; j<NODESHIDDEN1; j++){
            Weight* wp = new Weight(weightsHiddenArray[i][j]);
            layerOut[i]->addWeightIn(wp);
            layerHidden[j]->addWeightOut(wp);
        }
    }
    
    for(int i; i<NODESIN; i++){
        layerIn[i]->setValue(data[i][0]);
        cout<< layerIn[i]->getValue() <<"  ";
    }
    cout<<endl;
    for(int i; i<NODESHIDDEN1; i++){
        layerHidden[i]->calcValue();
        cout<< layerHidden[i]->getValue() <<" ";
    }
    cout<<endl;
    for(int i; i<NODESOUT; i++){
        layerOut[i]->calcValue();
        cout<< layerOut[i]->getValue() <<" ";
    }
    cout<<endl;
    return 0;
     /*
    */
}

