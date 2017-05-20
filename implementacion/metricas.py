"""
Corre `tests` n veces, una para cada tests/fold{i}.in
y reporta metricas.
"""

from test_config import *
import subprocess
import re

def rate(k):
    """ Devuelve el hitrate y matriz de confusión para los n test files.
    """
    rgx = re.compile(r'persona (\d+) -> (\d+)')
    success = 0
    total = 0

    for f in range(int(imagenes/fold_size)):
        filename = 'tests/fold{}.in'.format(f)
        res = subprocess.check_output(["./test.sh", str(k), filename])

        for l in res.splitlines():
            correct, guess = rgx.match(l.decode()).groups()
            total += 1
            success += 1 if correct == guess else 0

    return success / total

def find_k_nn():
    """ Busca el mejor k para kNN basandose en el hitrate.
    """
    for k in range(1, 16):
        hitrate = rate(k)
        print('k={}'.format(k), hitrate)

if __name__ == '__main__':
    find_k_nn()
