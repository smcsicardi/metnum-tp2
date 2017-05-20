"""
Corre `tests` n veces, una para cada tests/fold{i}.in
y reporta metricas.
"""

from test_config import *
import pandas as pd
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
            yield rgx.match(l.decode()).groups()


def confusion_matrix(results):
    """ Genera una matriz de confusión para una lista de
        tuplas (real, pred).
        Asume las personas se indexan desde 1.
    """
    l_real = []
    l_pred = []
    for real, pred in results:
        l_real.append(real)
        l_pred.append(pred)
    series_real = pd.Series(l_real, name='Actual')
    series_pred = pd.Series(l_pred, name='Predicted')
    return pd.crosstab(series_real, series_pred, margins=True)


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
