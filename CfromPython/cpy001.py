from ctypes import cdll,c_double,c_int,POINTER
lib = cdll.LoadLibrary('./libcpy.so')
lib.c_our_function.restype = c_int
lib.c_our_function.argtypes = (c_int, POINTER(c_int))

lib.c_our_function_double.restype = c_double
lib.c_our_function_double.argtypes = (c_int, POINTER(c_double))

lib.c_our_function_array.restype = POINTER(c_int*4)
lib.c_our_function_array.argtypes = (c_int, POINTER(c_int))




def barsum(numbers):
    num_numbers = len(numbers)
    array_type = c_int * num_numbers
    result = lib.c_our_function(c_int(num_numbers), array_type(*numbers))
    return int(result)

def barsumarray(numbers):
    num_numbers = len(numbers)
    array_type = c_int * num_numbers
    result = lib.c_our_function_array(c_int(num_numbers), array_type(*numbers))
    return result

def barsumarraydouble(numbers):
    num_numbers = len(numbers)
    array_type = c_double * num_numbers
    result = lib.c_our_function_double(c_int(num_numbers), array_type(*numbers))
    return result


a = [1,2,3,4]        
print(barsum(a))
res = barsumarray(a)
print([i for i in res.contents])
print(barsumarraydouble([1.2,3.0,5.6,7.8]))
