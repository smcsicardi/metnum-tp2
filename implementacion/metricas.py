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


def find_k_nn():
    """ Busca el mejor k para kNN basandose en el hitrate (por ahora)
    """
    for k in range(1, 5):
        results = execute(k)
        matrix = confusion_matrix(results)
        # sumo la diagonal
        correct = 0
        for x in range(1, personas + 1):
            correct += matrix[str(x)][str(x)]

        total = matrix['All']['All']
        print('k={}'.format(k), correct/total)

if __name__ == '__main__':
    find_k_nn()
