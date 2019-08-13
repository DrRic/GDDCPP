from ctypes import cdll,c_double
lib = cdll.LoadLibrary('./libmlp.so')
lib.MLP_run.restype = c_double
class Mlp(object):
    def __init__(self):
        self.obj = lib.MLP_new()

    def run(self):
        return lib.MLP_run(self.obj)
        
mlp = Mlp()
print(mlp.run())        
