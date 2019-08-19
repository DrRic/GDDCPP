/*
 * cpy001.cpp
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


#include <stdio.h>
#include <iostream>

using namespace std;

int adder = 0;
int our_function(int num_numbers, int *numbers) {
    int i;
    int sum = 0;
    for (i = 0; i < num_numbers; i++) {
        sum += numbers[i];
    }
    adder= sum;
    return sum;
}

double our_function_double(int num_numbers, double *numbers) {
    int i;
    double sum = 0;
    for (i = 0; i < num_numbers; i++) {
        sum += numbers[i];
    }
    return sum;
}

int* our_function_array(int num_numbers, int *numbers) {
    int i;
    int sum = 0;
    for (i = 0; i < num_numbers; i++) {
        numbers[i]+=1;
    };
    int* res = new int[4];
    for(int i=0; i<4; i++){
        res[i]=i+adder;
    };
    cout << "here"<< endl;
    return res;
}


extern "C" {
    int c_our_function(int num_numbers, int *numbers){
        return our_function(num_numbers,numbers);
    }
    double c_our_function_double(int num_numbers, double *numbers){
        return our_function_double(num_numbers,numbers);
    }
    int* c_our_function_array(int num_numbers, int *numbers){
        return our_function_array(num_numbers,numbers);
    }

}
