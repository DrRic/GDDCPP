

#include <iostream>
#include <math.h>  
#include "Node.h"
#include "Weight.h"
#include "Actfun.h"
#include "MLP.h"

using namespace std;

MLP::MLP(vector<int> nodesPerLayer,Actfun* relufun){
    layers = nodesPerLayer.size()-1;
    cout<< layers << endl;
     
    Actfun* fun = new Actfun();
    
    // Create first layer
    vector<Node*> v1;
    network.push_back(v1);
    for(int j=0; j<nodesPerLayer[0]; j++){
        network[0].push_back(new Node(fun)); 
    }
    // Create the hiden layer
    for(int l = 1; l<layers; l++){
        vector<Node*> v2;
        network.push_back(v2);
        for(int i=0; i<nodesPerLayer[l]; i++){
            network[l].push_back(new Node(relufun));
            for(int j=0; j<nodesPerLayer[l-1]; j++){
                Weight* wp = new Weight((rand_d()*2.0)-1.0);
                network[l][i]->addWeightIn(wp);
                network[l-1][j]->addWeightOut(wp);
            }
        }
        
    }
    // Create the output layer
    vector<Node*> v3;
    network.push_back(v3);
    for(int i=0; i<nodesPerLayer[layers]; i++){
        network[layers].push_back(new Node(fun));
        for(int j=0; j<nodesPerLayer[layers-1]; j++){
            Weight* wp = new Weight((rand_d()*2.0)-1.0);
            network[layers][i]->addWeightIn(wp);
            network[layers-1][j]->addWeightOut(wp);
        }
    }
    
}

double MLP::rand_d(){
    return ((double) rand() / (RAND_MAX)) ;
};

int MLP::getInputSize(){
    return network[0].size();
}

void MLP::setInput(int indx,double value){
    network[0][indx]->setOutput(value);
}

double MLP::train(double *y){
    double er = 0.0;    
        //Feedfoward
    for(int l=1; l<layers+1; l++){
        for(int j=0; j<network[l].size(); j++){
            network[l][j]->calcValue();
        }
    }
    
    //Errors
    for(int j=0; j<network[layers].size(); j++){
        network[layers][j]->setError(network[layers][j]->getOutput()-y[j]);
        er+=pow((network[2][j]->getOutput()-y[j]),2);
    }
    for(int l = layers-1; l>0; l--){
        for(int j=0; j<network[l].size(); j++){
            network[l][j]->calcError();
        }
    }
    
    // backprop
    for(int l = layers; l>0; l--){
        for(int j=0; j<network[l].size(); j++){
            network[l][j]->backProp();
        }
    }
    
    return er;
}
