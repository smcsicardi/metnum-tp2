from test_config import *
import numpy as np
import subprocess
import pandas as pd
import re
from math import sqrt, fsum


def centroides(m):
    centrs = []
    k = 0
    for x in range(0,len(m),5):
        centrs.append(m[x][:])
        for i in range(1,5):
            for j in range(len(m[0])):
                centrs[k][j] += m[x+i][j]
        for i in range(len(centrs[k])):
            centrs[k][i] /= float(len(m[0]))
        k+=1
    return centrs

def checkCara(m,nuevoPunto):
    centrs = centroides(m)
    #print (len(centrs))
    dists = distancias(m,centrs)
    #print (dists)

    calc = [dist(nuevoPunto,p1) for p1 in centrs]
    for i in range(len(dists)):
        if (calc[i] < dists[i]*2):
            print ("pertenece al cara-space")
            return
    print ("no pertenece al cara-space")



def dist(p1, p2):
    return sqrt(fsum((p1[i]-p2[i])**2 for i in range(len(p1))))

def distancias(m,centros):
    calc = [[m[i][j]-centros[int(i/5)][j] for j in range(len(m[0]))] for i in range(len(m))]
    dists = [sqrt(fsum(x**2 for x in calc[j])) for j in range(1,len(m))]
    res = [max(dists[j*5:j*5+5]) for j in range(41)]
    return res
    


def check():
    df = pd.read_csv('csv/X2.csv')
    m = df.values.tolist()
    n = int(input())
    l = [input() for i in range(n)]
    #print (n)
    #print (l, type(l[0]))
    #print("\n")
    checkCara(m,l)



if __name__ == '__main__':
    check()
