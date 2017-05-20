"""
Genera k folds de tamaño `size` y los guarda como fold{i}.in
"""

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


imgs = [str(i + 1) for i in range(imagenes)]
shuffle(imgs)
folds = list(chunks(imgs, fold_size))

for i, fold in enumerate(folds):
    with open('tests/fold{}.in'.format(i), 'w') as f:
        f.write('../data/ImagenesCarasRed/ 28 23 41 {} {}\n'.format(9 - size, pca_n))
        f.write('\n')

        others = folds[0 : i] + folds[i+1 : int(imagenes/size)]
        others_flat = [x for y in others for x in y]

        for p in range(personas):
            f.write('s{}/ '.format(p+1) + ' '.join(others_flat))
            f.write('\n')

        f.write(str(personas))
        f.write('\n')
        for p in range(personas):
            for img in fold:
                f.write('../data/ImagenesCarasRed/s{}/{}.pgm {}'.format(p+1, img, p+1))
                f.write('\n')
    print(f.name, '✔')
