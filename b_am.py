import math
import numpy as np

A = [[-3, 3, -1, 1, 1, 0, 0, 0, 0],
     [-1, 1, -2, 2, 0, 1, 0, 0, 0],
     [1, -1, -1, 1, 0, 0, 1, 0, 0],
     [1, -1, 0, 0 , 0, 0, 0, 1, 0],
     [0, 0, 1, -1 , 0, 0, 0, 0, 1]]
A = np.float64(A)
A[0] = (-1)*A[0]
A[1] = (-1)*A[1]

delta = np.zeros(len(A[0]), dtype = np.float64)
C_all = [-1, 1, 1, -1]

B = [-3, -4, 1, 5, 5]
B[0] = (-1)*B[0]
B[1] = -(1)*B[1]

S = 0

print (A)
print (B)