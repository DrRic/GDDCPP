

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
void MLP::init(int num_numbers, int *numbers,double dropout){
    vector<int> nodesPerLayer;
    Weight::alpha  = 0.002;
    //cout << num_numbers << endl;
    for (int i = 0; i < num_numbers; i++) {
        nodesPerLayer.push_back(numbers[i]);
        //cout << numbers[i] << endl;
    }
    layers = nodesPerLayer.size()-1;
    srand(time(nullptr)); 
    Actfun* fun = new Actfun();
    Actfun* relufun = new Relufun();
    // Create first layer
    vector<Node*> v1;
    network.push_back(v1);
    for(int j=0; j<nodesPerLayer[0]; j++){
        network[0].push_back(new Node(fun,0.0)); 
    }
    // Create the hiden layer
    for(int l = 1; l<layers; l++){
        vector<Node*> v2;
        network.push_back(v2);
        for(int i=0; i<nodesPerLayer[l]; i++){
            network[l].push_back(new Node(relufun,dropout));
            for(int j=0; j<nodesPerLayer[l-1]; j++){
                Weight* wp = new Weight((rand_d()*0.2)-0.1);
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
        network[layers].push_back(new Node(fun,0.0));
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

int MLP::getOutput(){
    double xmax = 0.0;
    int xpos = 0;
    for(int j=0; j<network[layers].size(); j++){
        if(network[layers][j]->getOutput()>xmax){
            xmax = network[layers][j]->getOutput();
            xpos =j;
        } 
    }
    return xpos;
} 

int MLP::countCorrect(vector<double> *y){
    double xmax = 0.0;
    double ymax = 0.0;
    int xpos = 0;
    int ypos = 0;
    for(int j=0; j<network[layers].size(); j++){
        if(network[layers][j]->getOutput()>xmax){
            xmax = network[layers][j]->getOutput();
            xpos =j;
        } 
        if(y->at(j)>ymax){
            ymax = y->at(j);
            ypos = j;
        };
    }
    if(xpos == ypos){
        return 1;
    }
    return 0;
}

void MLP::feedFoward(vector<double> *X){
    
    for(int i=0; i<network[0].size(); i++){
        //cout << X->at(i) << " ";
        network[0][i]->setOutput(X->at(i));
    }
        //Feedfoward
    for(int l=1; l<network.size(); l++){
        for(int j=0; j<network[l].size(); j++){
            network[l][j]->calcValue();
        }
    }
}

double MLP::train( vector<double> *X, vector<double> *y){
    double ersum = 0.0;
    this->feedFoward(X);
    

    //Errors
    for(int j=0; j<network[layers].size(); j++){
        double er = network[layers][j]->getOutput()-y->at(j);
        network[layers][j]->setError(er);
        ersum+=er*er;
    }
    for(int l = layers-1; l>0; l--){
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

vector<vector<double>> trainX,trainY;

MLP mlp = MLP();
void addXData(int num_numbers, double *numbers) {
    vector<double> row;
    for(int i=0; i<num_numbers; i++){
        row.push_back(numbers[i]);
    }
    trainX.push_back(row);
}

void addYData(int num_numbers, double *numbers) {
    vector<double> row;
    for(int i=0; i<num_numbers; i++){
        row.push_back(numbers[i]);
    }
    trainY.push_back(row);
}

int predict(int num_numbers, double *numbers) {
    vector<double> row;
    for(int i=0; i<num_numbers; i++){
        row.push_back(numbers[i]);
    }
    mlp.feedFoward(&row);
    return mlp.getOutput();
}

int getXDataSize(){
    return trainX.size();
}
int getYDataSize(){
    return trainY.size();
}

void trainMLP(){
    for(int i=0; i<trainX.size(); i++){
        mlp.train(&trainX[i],&trainY[i]);
    }
}

double* trainWithResults(){
    double er = 0.0;
    double error = 0.0;
    int count=0;
    for(int i=0; i<trainX.size(); i++){
        er = mlp.train(&trainX[i],&trainY[i]);
        error+= er;
        if(mlp.countCorrect(&trainY[i])>0){
            count++;
        }
    }
    double* res = new double[2];
    res[0] = error/trainX.size();
    res[1] = (count*1.0)/trainX.size();
    return res;
}

extern "C" {
    void MLP_init(int num_numbers, int *numbers,double dropout){ 
        mlp.init(num_numbers,numbers,dropout); 
    }
    
    void MLP_train(){
        trainMLP(); 
    }
    
    double* MLP_train_with_results(){
        return trainWithResults();
    }

    
    int MLP_predict(int num_numbers, double *numbers){
        return predict(num_numbers, numbers);
    }    
    
    void add_x_data(int num_numbers, double *numbers){
        addXData(num_numbers, numbers);
    }
    
    void add_y_data(int num_numbers, double *numbers){
        addYData(num_numbers, numbers);
    }
    
    int get_x_data_size(){
        return getYDataSize();
    }

    int get_y_data_size(){
        return getYDataSize();
    }
}
