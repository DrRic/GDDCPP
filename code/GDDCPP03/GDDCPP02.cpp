#include <iostream>
#include <cmath>
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
    double weightsArray_0_1[4][3] = {
        {-0.16595599,  -0.70648822, -0.20646505},
        {0.44064899, -0.81532281, 0.07763347},
        {-0.99977125, -0.62747958, -0.16161097},
        {-0.39533485, -0.30887855,  0.370439}
    }; 
    double weightsArray_1_2[4][1] = {
        {-0.5910955 },
        {0.75623487},
        {-0.94522481},
        {0.34093502}
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
        network[2].push_back(new Node(actfun));
        for(int j=0; j<nodesPerLayer[1]; j++){
            Weight* wp = new Weight(weightsArray_1_2[i][j]);
            network[2][i]->addWeightIn(wp);
            network[1][j]->addWeightOut(wp);
        }
    }

    for(int it=0; it<1; it++){
        double er = 0;
        for(int k=0; k<4; k++){
            // Populate the input layer with data
            for(int i=0; i<network[0].size(); i++){
                network[0][i]->setOutput(X[k][i]);
                //cout<< network[0][i]->getOutput() <<"  ";
            }
            //cout<<endl;
            
            // hidden layer
            for(int j=0; j<network[1].size(); j++){
                network[1][j]->calcValue();
                cout<< network[1][j]->getOutput() << " " ;
            }
            cout<<endl;

            // output layer
            for(int j=0; j<network[2].size(); j++){
                network[2][j]->calcValue();
                cout<< network[2][j]->getOutput() << " ";
            }
            cout<<endl;

            // calculate the ouput error
            for(int j=0; j<network[2].size(); j++){
                network[2][j]->setError(network[2][j]->getOutput()-y[k]);
                er+=pow((network[2][j]->getOutput()-y[k]),2);
            }
            cout<< er <<endl;

            // calculate the hidden error
            for(int j=0; j<network[1].size(); j++){
                network[1][j]->calcError();
                //cout<< network[1][j]->getError() <<endl;
            }
            //cout<<endl;

            // backprop the ouput error
            for(int j=0; j<network[2].size(); j++){
                network[2][j]->backProp();
            }
            //cout<<endl;
            
             // backprop the hidden error
            for(int j=0; j<network[1].size(); j++){
                network[1][j]->backProp();
            }
            //cout<<endl;
        }
        if(it % 10 == 0){
            cout<<endl<< it << " "<< er << endl;
        }
    }
    return 0; 
}

