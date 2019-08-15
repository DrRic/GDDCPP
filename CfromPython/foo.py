from ctypes import cdll,c_double,c_int,POINTER
lib = cdll.LoadLibrary('./libfoo.so')
lib.Foo_bar.restype = c_double

lib.Foo_baradd.restype = c_int
lib.Foo_baradd.argtype = c_int

lib.Foo_baradddouble.restype = c_double
lib.Foo_baradddouble.argtype = c_double

lib.Foo_barsum.restype = c_double
lib.Foo_barsum.argtypes = [c_int, POINTER(c_double)]

class Foo(object):
    def __init__(self):
        self.obj = lib.Foo_new()

    def bar(self):
        print(lib.Foo_bar(self.obj))
        
    def baradd(self,number):
        result = lib.Foo_baradd(self.obj,c_int(number))
        return int(result)

    def baradddouble(self,number):
        result = lib.Foo_baradddouble(self.obj,c_double(number))
        return result
        
    def barsum(self,numbers):
        num_numbers = len(numbers)
        array_type = c_double * num_numbers
        result = lib.Foo_barsum(self.obj,c_double(int(num_numbers)),c_int(num_numbers), array_type(*numbers))
        return result

        
f = Foo()
f.bar()        
print(f.baradd(1))
print(f.baradddouble(1.6))
print(f.barsum([1.1,2.1,3.1,4.1]))
