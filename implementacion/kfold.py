"""
Genera k folds de tamaño `fold_size` y los guarda como fold{i}.in
"""

import sys
from test_config import *
from random import shuffle
from collections import defaultdict


def group(l):
    d = defaultdict(list)
    for p, i in l:
        d[p].append(i)
    return d


def chunks(l, n):
    for i in range(0, len(l), n):
        yield l[i:i + n]


def generate(pca_n):
    imgs = [str(i + 1) for i in range(imagenes)]
    shuffle(imgs)
    folds = list(chunks(imgs, fold_size))

    for i, fold in enumerate(folds):
        with open('tests/fold{}.in'.format(i), 'w') as f:
            f.write('../data/ImagenesCarasRed/ 28 23 {} {} {}\n'.format(
                personas, imagenes - fold_size, pca_n))
            f.write('\n')

            others = folds[0 : i] + folds[i+1 : fold_count]
            others_flat = [x for y in others for x in y]

            for p in range(personas):
                f.write('s{}/ '.format(p+1) + ' '.join(others_flat))
                f.write('\n')

            # cant de instancias de test
            f.write(str(personas * fold_size))
            f.write('\n')
            for p in range(personas):
                for img in fold:
                    f.write('../data/ImagenesCarasRed/s{}/{}.pgm {}'.format(p+1, img, p+1))
                    f.write('\n')
        print(f.name, '✔')

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Uso: python3 kfold.py <cant_componentes_principales>')
    else:
        generate(sys.argv[1])
