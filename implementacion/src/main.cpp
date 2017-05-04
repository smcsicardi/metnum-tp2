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

    vector<unsigned char> what = levantarImagen("../data/ImagenesCarasRed/s1/2.pgm");

    for (auto x : what){
        cout << (int)x << ",";
    }
    // imprimirMatriz(what);

    return 0;
}
