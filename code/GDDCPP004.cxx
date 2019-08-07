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
        Node* to;
        Node* from;
    public:
        Weight(double value){
            this->value = value;
        }

        double getValue(){
            return value;
        }
        
        void setTo(Node* to){
            this->to = to;
        }
        
        void setFrom(Node* from){
            this->from = from;
        }
        //double getTo(){
        //    return to->getValue();
        //}
};

class Node{
    private:
        double value,output,error;
        vector<Weight *> weightsIn,weightsOut;
    public:
        Node(){
            this->value=0.0;
            this->output=0.0;
            this->error=0.0;
        }

        void addWeightIn(Weight* wp){
            wp->setTo(this);
            this->weightsIn.push_back(wp);
        }
        
        void addWeightOut(Weight* wp){
            wp->setFrom(this);
            this->weightsOut.push_back(wp);
        }
        
        void setValue(double value){
            this->value = value;
        }
        
        double getValue(){
            return this->value;
        }
        
        double getWeightVal(){
            return weightsIn[0]->getValue();
        }
        
};

int main(int argc, char **argv){
    Weight* wpIn = new Weight(0.1);
    Weight* wpOut = new Weight(0.2);
    Node* nodep = new Node();
    nodep->setValue(0.3);
    nodep->addWeightIn(wpIn);
    nodep->addWeightOut(wpOut);
    cout << "Node value:"<<nodep->getWeightVal()<<endl;
	return 0;
}

