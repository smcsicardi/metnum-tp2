"""
Corre `tests` n veces, una para cada tests/fold{i}.in
y reporta metricas.
"""

import time
from test_config import *
import numpy as np
import kfold
import subprocess
import re

def execute(k):
    """ Devuelve un iterador de tuplas (real, pred).
    """
    rgx = re.compile(r'persona (\d+) -> (\d+)')

    for f in range(fold_count):
        filename = 'tests/fold{}.in'.format(f)
        res = subprocess.check_output(["./test.sh", str(k), filename])

        for l in res.splitlines():
            a, b = rgx.match(l.decode()).groups()
            yield (int(a), int(b))


def confusion_matrix(results):
    """ Genera una matriz de confusión para una lista de
        tuplas (real, pred).
        Asume las personas se indexan desde 1.
    """
    matrix = np.zeros((personas, personas))
    for real, pred in results:
        matrix[real-1, pred-1] += 1
    return matrix


def stats_hitrate():
    diag = np.arange(personas)
    with open('csv/hitrate_ambos.csv', 'w') as f:
        f.write('imagenes,hitrate,componentes,k')
        f.write('\n')
        diag = np.arange(personas)
        for g in [15,25,35]:
            for k in [1,5,10]:
                kfold.generate(g)

                r = execute(k)
                m = confusion_matrix(r)
                hitrate = m[diag, diag] / imagenes
                for h in hitrate:
                    f.write('{},{},{},{}'.format(imagenes-fold_size,h, g, k))
                    f.write('\n')



def stats_precision():
    with open('csv/precision.csv', 'w') as f:
        f.write('precision,componentes,k')
        f.write('\n')
        diag = np.arange(personas)
        for g in [15,25,35]:
            for k in [1,5,10]:
                kfold.generate(g)

                r = execute(k)
                m = confusion_matrix(r)
                precision = m[diag, diag] / np.sum(m, axis=1)
                for p in precision:
                    f.write('{},{},{}'.format(p, g, k))
                    f.write('\n')



def stats_avg(matrix):
    """ Devuelve el promedio de precision y hitrate
        de cada persona.
        Precision puede tener denominador 0 por lo que
        saco esos casos del promedio.
    """
    diag = np.arange(personas)

    col_sum = np.sum(matrix, axis=0)
    count = 0
    precision = 0
    for i in diag:
        if col_sum[i] == 0: continue
        precision += matrix[i,i] / col_sum[i]
        count += 1
    precision = precision / count

    hitrate = np.sum(matrix[diag, diag]) / np.sum(matrix)
    return hitrate, precision


def find_k_nn():
    """ Busca el mejor k para kNN basandose en el hitrate (por ahora)
    """
    for k in range(1, 15):
        results = execute(k)
        matrix = confusion_matrix(results)
        # sumo la diagonal
        s = stats(matrix)
        print('k={} -> '.format(k), s)


def gamma_vs_time():
    with open('csv/times.csv', 'w') as f:
        f.write('time,componentes')
        f.write('\n')
        for g in np.arange(1, 40, 4):
            kfold.generate(g)

            r = execute(1)
            start = time.time()
            list(r)
            end = time.time()

            f.write('{},{}'.format(end-start, g))
            f.write('\n')


def todo_vs_gamma():
    with open('csv/todo2.csv', 'w') as f:
        f.write('hitrate,precision,componentes')
        f.write('\n')
        for g in [100, 120]:

            kfold.generate(g)

            r = execute(1)
            m = confusion_matrix(r)
            hr, pr = stats_avg(m)
            f.write('{},{},{}'.format(hr, pr, g))
            f.write('\n')


def gamma_vs_k():
    with open('csv/hitrates.csv', 'w') as f:
        f.write('hitrate,componentes,k')
        f.write('\n')
        for g in [1, 5, 10, 15]:
            for k in np.arange(1, 20, 2):

                kfold.generate(g)

                r = execute(k)
                m = confusion_matrix(r)
                hr, pr = stats_avg(m)
                f.write('{},{},{}'.format(hr, g, k))
                f.write('\n')
