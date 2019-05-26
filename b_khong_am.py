import math
import numpy as np

#Input zone
matrixA = [[1, -1, 2],
           [3, -3, 2],
           [3, -3, 1]]

A = [[1, -1, 2, 1, 0, 0],
     [3, -3, 2, 0, 1, 0],
     [3, -3, 1, 0, 0, 1]]

delta = np.zeros(len(A[0]), dtype=np.float64)
C_all = [1, 1, -1, 0, 0, 0]

S = 0

X = ['x1', 'x2', 'x3', 'x4', 'x5', 'x6']
X_real = ['x1', 'x2', 'x3']
X_cs = ['x4', 'x5', 'x6']

B = [48, 36, 30]
C = np.zeros(len(X_cs), dtype=np.float64)
lamda = np.zeros(len(X_cs), dtype=np.float64)

def cal_delta(i):
    result=0
    for c, d in zip(C, A[:,i]):
        result += c*d
    result -= C_all[i]
    return result

def cal_S():
    result=0
    for c, b in zip(C, B):
        result+=c*b
    return result

def kduong(x):
    for i in x:
        if i > 0:
            return False
    return True 

def find_max(x):
    maxx = 0
    it = -1
    for i in range(len(x)):
        if x[i]>=maxx:
            it = i
            maxx=x[i]
    return it

def find_duong_min(x):
    minn = 999
    it = -1
    for i in range(len(x)):
        if x[i]<=minn and x[i]>0:
            it = i
            minn=x[i]
    return it

if __name__=='__main__':
    print("b>0")
    
    A = np.array(A, dtype=np.float64)
    m, n = A.shape

    count_loop=0
    while (True):
        print ("loop", count_loop)
        print ("X_cs: ", X_cs)
        print (A)
        for i in range(n):
            delta[i] = cal_delta(i)
    
        if not kduong(delta):
            column = find_max(delta)
            #lamda = B/A[:, column]
            for i in range(len(lamda)):
                if A[i][column]!=0:
                    lamda[i] = B[i]/A[i][column]
                else:
                    lamda[i] = -999
            row = find_duong_min(lamda)
            if row == -1:
                print("vo nghiem")
                break
            #print (lamda)
            #print (X_cs[row],'ra ', X[column], 'vao ')
            X_cs[row] = X[column]
            C[row] = C_all[column]

            #print ("C: ", C)
            #print ("C all: ", C_all)

            pivot = A[row][column]
            A[row,:] = A[row,:]/pivot
            #print ("pivot:", pivot)
            
            B[row] = B[row]/pivot
            for rw in range(m):
                if rw!=row:
                    d = A[rw][column]
                    A[rw] = A[rw] - d*A[row]
                    B[rw]=B[rw] - d*B[row]
            S = cal_S()
        else:
            print ("Done, Z=", S)
            for x in X_real:
                if x in X_cs:
                    print (x, ':', B[X_cs.index(x)])
                else:
                    print(x, ':', 0)
            break
        count_loop+=1
