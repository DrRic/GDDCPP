#!/usr/bin/env python
# coding: utf-8

# In[1]:


from ctypes import cdll,c_double,c_int,POINTER
lib = cdll.LoadLibrary('./libmlp.so')
lib.add_x_data.argtypes = (c_int, POINTER(c_double))
lib.add_y_data.argtypes = (c_int, POINTER(c_double))
lib.get_x_data_size.restype = c_int
lib.get_y_data_size.restype = c_int

lib.MLP_init.argtypes = (c_int, POINTER(c_int))
lib.MLP_train.restype = c_double


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
    
def initilise(layout):
    num_numbers = len(layout)
    array_type = c_int * num_numbers
    lib.MLP_init(c_int(num_numbers), array_type(*layout))
    


# In[9]:


filepath = '../../../data/mnist.csv'
inputs =0
outputs = 0
with open(filepath, "r") as ins:
    first_line = ins.readline()
    a,b = first_line.strip().split(',')
    inputs=int(a)
    outputs=int(b)
    count = 0
    for line in ins:
        data = line.strip().split(',')
        count+=1
        del data[-1]
        data = list(map(float, data))
        push_x_row(data[:inputs])
        push_y_row(data[inputs:])
print(count)


# In[ ]:

print(inputs,outputs)
initilise([inputs,40,outputs])

for i in range(200):
    er = train()
    if( i % 10 == 0):
        print(i,er)
# In[5]:


a


# In[ ]:




