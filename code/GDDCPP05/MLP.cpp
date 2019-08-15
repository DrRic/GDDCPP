

#include <iostream>
#include <math.h>  
#include <ctime>
#include <cstdlib>
#include "Node.h"
#include "Weight.h"
#include "Actfun.h"
#include "MLP.h"

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

MLP::MLP(){
}
void MLP::init(int num_numbers, int *numbers){
    vector<int> nodesPerLayer;
    for (int i = 0; i < num_numbers; i++) {
        nodesPerLayer.push_back(numbers[i]);
    }
    layers = nodesPerLayer.size()-1;
    srand(time(nullptr)); 
    Actfun* fun = new Actfun();
    Actfun* relufun = new Relufun();
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
                weights.push_back(wp);
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
            weights.push_back(wp);
            network[layers][i]->addWeightIn(wp);
            network[layers-1][j]->addWeightOut(wp);
        }
    }
    
}

double MLP::rand_d(){
    return ((double) rand() / (RAND_MAX)) ;
};

double MLP::train(int numX, double *X, int numy, double *y){
    double ersum = 0.0;
    
    for(int i=0; i<network[0].size(); i++){
        network[0][i]->setOutput(X[i]);
    }
        //Feedfoward
    for(int l=1; l<network.size(); l++){
        for(int j=0; j<network[l].size(); j++){
            network[l][j]->calcValue();
        }
    }
    
    //Errors
    for(int j=0; j<network[layers].size(); j++){
        double er = network[layers][j]->getOutput()-y[j];
        network[layers][j]->setError(er);
        ersum+=er*er;
    }
    for(int l = layers-1; l>0; l--){
        cout<< l << endl;
        for(int j=0; j<network[l].size(); j++){
            network[l][j]->calcError();
        }
    }
    
    // backprop
    for(int i=0; i<weights.size(); i++){
        weights[i]->updateWeight();
    }
    
    return ersum;
}

extern "C" {
    MLP* MLP_new(){ 
        return new MLP(); 
    }
    void MLP_init(MLP* mlp,int x, int num_numbers, int *numbers){ 
        cout<< x<< " "<<num_numbers << endl;
        mlp->init(num_numbers,numbers); 
    }
    double MLP_train(MLP* mlp, int x, int numX, double *X, int numy, double *y){ 
        return mlp->train(numX,X,numy,y); 
    }
}
