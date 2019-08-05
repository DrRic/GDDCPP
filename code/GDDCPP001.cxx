/*
 * GDDCPP001.cxx
 * 
 * Copyright 2019  <pi@raspberrypi>
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

#include <vector>
#include <iostream>
using namespace std;

class Node;
class Weight{
    private:
        double value;
    public:
        Weight(double value){
            this->value = value;
        }
        double getValue(){
            return this->value;
        }
};

int main(int argc, char **argv){
    Weight* wp = new Weight(0.5);
    Weight w =  Weight(0.3);
    
    cout << "hello real world " << w.getValue() << endl;
	cout << "hello pointy world " << wp->getValue() << endl;
	return 0;
}

