#include <stdio.h>
#include <iostream>
#include <vector>
#include "MLP.h"

using namespace std;

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

int getXDataSize(){
    return trainX.size();
}
int getYDataSize(){
    return trainY.size();
}

double trainMLP(){
    double er = 0.0;
    double error = 0.0;
    for(int i=0; i<trainX.size(); i++){
        er = mlp.train(&trainX[i],&trainY[i]);
        //cout << i << "  " << er << endl;
        error+= er ;//mlp.train(&trainX[i],&trainY[i]);
    }
    return error/trainX.size();
}

extern "C" {
    void MLP_init(int num_numbers, int *numbers){ 
        mlp.init(num_numbers,numbers); 
    }
    
    double MLP_train(){
        return trainMLP(); 
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
