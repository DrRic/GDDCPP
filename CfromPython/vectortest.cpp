#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

vector<double> test;
void pop_vector(){
    for(int i=0; i<10; i++){
        test.push_back(i+7);
    } 
}

void print_vector(vector<double> *v){
    for(int i=0; i<v->size(); i++){
        cout << v->at(i) << endl;
    }
}


int main(int argc, char **argv)
{
	pop_vector();
    print_vector(&test);
	return 0;
}
