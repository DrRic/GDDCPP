#include <iostream>
using namespace std;

class Foo{
    public:
        double bar(){
            return 9.999;
        }
        int baradd(int num_numbers) {
            return num_numbers*2;
        }
        int barsum(int num_numbers, int *numbers) {
            int sum = 0;
            cout<< num_numbers << endl;
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
    int Foo_barsum(Foo* foo, int num_numbers, int *numbers){ 
        return foo->barsum(num_numbers,numbers); 
    }
}
