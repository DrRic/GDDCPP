from ctypes import cdll,c_double,c_int,POINTER
lib = cdll.LoadLibrary('./libmlp.so')
lib.MLP_init.argtypes = [c_int, POINTER(c_int)]
class Mlp(object):
    def __init__(self):
        self.obj = lib.MLP_new()
    
    def initilise(self,struct):   
        num_numbers = len(struct)
        array_type = c_double * num_numbers
        lib.MLP_init(self.obj,c_int(num_numbers),array_type(*struct)) 

mlp = Mlp()
mlp.initilise([3,4,1])
       
