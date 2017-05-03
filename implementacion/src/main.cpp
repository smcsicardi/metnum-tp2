#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <string>
#include "lib/pgm_reader.h"
#include "lib/utilities.h"

using namespace std;


int main(int argv, char* argc[]){
    Input input;

    levantarDatos(input);
    imprimirDatos(input);

    // int lol = levantarMatriz("../data/ImagenesCaras/s1/2.pgm");

    // prueba levanto una imagen y la paso a matriz
    //FILE *imagen;
    //imagen = fopen("../data/ImagenesCaras/s1/1.pgm", "r+");

    //int img[filas][columnas] = (int**) imagen;

    return 0;
}
