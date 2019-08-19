#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<double>> trainX,trainY;
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

extern "C" {
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
