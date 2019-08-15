#include <iostream>
using namespace std;

class Foo{
    public:
        double bar(){
            return 19.999;
        }
        int baradd(int num_numbers) {
            return num_numbers*2;
        }
        double baradddouble(double num_numbers) {
            return num_numbers*2;
        }
        double barsum(int num_numbers, double *numbers) {
            double sum = 0;            
            for (int i = 0; i < num_numbers; i++) {
                sum += numbers[i];
            }
            return sum;
        }
};
extern "C" {
    Foo* Foo_new(){ return new Foo(); }
    double Foo_bar(Foo* foo){ 
        return foo->bar(); 
    }
    int Foo_baradd(Foo* foo, int num_numbers){ 
        return foo->baradd(num_numbers); 
    }
    double Foo_baradddouble(Foo* foo, double num_numbers){ 
        return foo->baradddouble(num_numbers); 
    }
    double Foo_barsum(Foo* foo,int x, int num_numbers, double *numbers){ 
        return foo->barsum(num_numbers,numbers); 
    }
}
