"""
Corre `tests` n veces, una para cada tests/fold{i}.in
y reporta metricas.
"""

from test_config import *
import numpy as np
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


def stats(matrix):
    """ Devuelve el promedio de precision, recall y hitrate
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

    recall = np.average(matrix[diag, diag] / np.sum(matrix, axis=1))
    hitrate = np.sum(matrix[diag, diag]) / np.sum(matrix)
    return precision, recall, hitrate


def find_k_nn():
    """ Busca el mejor k para kNN basandose en el hitrate (por ahora)
    """
    for k in range(1, 15):
        results = execute(k)
        matrix = confusion_matrix(results)
        # sumo la diagonal
        s = stats(matrix)
        print('k={} -> '.format(k), s)


if __name__ == '__main__':
    find_k_nn()
