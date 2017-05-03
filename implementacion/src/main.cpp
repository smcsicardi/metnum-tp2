#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>

#include "lib/tipos.h"
#include "lib/pgm_reader.h"
#include "lib/utilities.h"

using namespace std;

int main(int argv, char* argc[]){
    Input input;

    levantarDatos(input);
    imprimirDatos(input);

    matriz what = levantarMatriz("../data/ImagenesCarasRed/s1/2.pgm");

    // imprimirMatriz(what);

    return 0;
}
