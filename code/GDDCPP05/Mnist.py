#!/usr/bin/env python
# coding: utf-8

# In[1]:

import random
from ctypes import cdll,c_double,c_int,POINTER
lib = cdll.LoadLibrary('./libmlpc.so')
lib.add_x_data.argtypes = (c_int, POINTER(c_double))
lib.add_y_data.argtypes = (c_int, POINTER(c_double))
lib.get_x_data_size.restype = c_int
lib.get_y_data_size.restype = c_int

lib.MLP_init.argtypes = (c_int, POINTER(c_int),c_double)
lib.MLP_train.restype = c_double

lib.MLP_train_with_results.restype = POINTER(c_double*2)

lib.MLP_predict.argtypes = (c_int, POINTER(c_double))
lib.MLP_predict.restype = c_int


# In[8]:


def push_x_row(numbers):
    num_numbers = len(numbers)
    array_type = c_double * num_numbers
    lib.add_x_data(c_int(num_numbers), array_type(*numbers))

def push_y_row(numbers):
    num_numbers = len(numbers)
    array_type = c_double * num_numbers
    lib.add_y_data(c_int(num_numbers), array_type(*numbers))
    
def train():
    return lib.MLP_train()
    
def train_with_results():
    res = lib.MLP_train_with_results();
    return res.contents[0],res.contents[1]
    
def initilise(layout,dropout):
    num_numbers = len(layout)
    array_type = c_int * num_numbers
    lib.MLP_init(c_int(num_numbers), array_type(*layout),dropout)

def predict(numbers):
    num_numbers = len(numbers)
    array_type = c_double * num_numbers
    return lib.MLP_predict(c_int(num_numbers), array_type(*numbers))
    


# In[9]:


filepath = '../../../data/mnist.csv'
inputs =0
outputs = 0
testlist=[]
with open(filepath, "r") as ins:
    first_line = ins.readline()
    a,b = first_line.strip().split(',')
    inputs=int(a)
    outputs=int(b)
    count = 0
    for line in ins:
        data = line.strip().split(',')
        del data[-1]
        data = list(map(float, data))
        if random.random()<0.8:
            push_x_row(data[:inputs])
            push_y_row(data[inputs:])
        else:
            testlist.append(count)
        count+=1
        
print(count,len(testlist))


# In[ ]:

print(inputs,outputs)
initilise([inputs,100,40,outputs],0.1)

for i in range(501):
    if( i % 10 == 0):
        print(i,train_with_results())
    else:
        train()
# In[5]:


with open(filepath, "r") as ins:
    first_line = ins.readline()
    a,b = first_line.strip().split(',')
    inputs=int(a)
    outputs=int(b)
    count = 0
    correct = 0
    for line in ins:
        data = line.strip().split(',')
        
        del data[-1]
        data = list(map(float, data))
        if count in testlist:
            y = data[inputs:].index(max(data[inputs:]));
            p =predict(data[:inputs]) 
            if(p==y ):
                correct+=1;
        count+=1
print(len(testlist),correct/len(testlist))


# In[ ]:




