import numpy as np

def lin():
    v1 = np.array(list(map(int, input().split())))
    v2 = np.array(list(map(int, input().split())))
    v3 = np.array(list(map(int, input().split())))
    

    for i in range(-10,11):
        for j in range(-10,11):
            if (i * v1 + j * v2 == v3).all():
                print(i, j)
                return
    print("NO_SOLUTION")
lin()