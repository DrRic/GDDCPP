from ctypes import cdll,c_double,c_int,POINTER
lib = cdll.LoadLibrary('./libfoo.so')
lib.Foo_bar.restype = c_double
lib.Foo_baradd.restype = c_int
lib.Foo_baradd.argtype = c_int
lib.Foo_barsum.restype = c_int
lib.Foo_barsum.argtypes = [c_int, POINTER(c_int)]

class Foo(object):
    def __init__(self):
        self.obj = lib.Foo_new()

    def bar(self):
        print(lib.Foo_bar(self.obj))
        
    def baradd(self,number):
        result = lib.Foo_baradd(self.obj,c_int(number))
        return int(result)
        
    def barsum(self,numbers):
        num_numbers = len(numbers)
        array_type = c_int * num_numbers
        result = lib.Foo_baradd(self.obj,c_int(num_numbers), array_type(*numbers))
        return int(result)

        
f = Foo()
f.bar()        
print(f.baradd(1))
print(f.barsum([1,2,3,4]))
