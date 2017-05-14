#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <string>

#include "lib/tipos.h"
#include "lib/pgm.h"
#include "lib/utilities.h"
#include "lib/linalg.h"
#include "lib/parser.h"

using namespace std;

int main(int argv, char* argc[]){
    Input input = levantarDatos();
    Matriz X = obtenerMatrizX(input);

    Matriz M = multiplicarXXt(X);
    vector<EigenVV> ac = obtenerAutoCaras(M, input);


    // y = Xt*autoVector
    vector<double> y (X.columnas);
    for (auto j = 0; j < X.columnas; j++){
        double tmp = 0;
        for (auto i = 0; i < X.filas; i++){
            tmp += X.datos[i][j] * ac[0].autoVector[i];
        }
        y[j] = tmp;
    }

    imprimirVector(ac[0].autoVector);

    escribirImagen(vectorAImagen(y),
                   input.ancho,
                   input.alto,
                   "lol2.pgm");

    //imprimirVector(transformacionCaracteristica(ac, input.vTests[0].img));

    return 0;
}
