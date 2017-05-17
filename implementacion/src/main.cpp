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

int main(int argc, char* argv[]){
    Input input = levantarDatos();
    Matriz X = obtenerMatrizX(input);

    // indefinido si cantComponentes > X.filas
    vector<EigenVV> autoCaras (input.cantComponentes);
    Matriz M;

    if (argc <= 1) {
        // sin argumentos hace Xt*X
        M = multiplicarXtX(X);
        autoCaras = obtenerAutoVV(M, input.cantComponentes);
    } else {
        if (string(argv[1]) == "--fast"){
            // con --fast hace X*Xt y después genera las autoCaras
            M = multiplicarXXt(X);
            vector<EigenVV> autoVV = obtenerAutoVV(M, input.cantComponentes);

            // autoCaras_k = Xt*autoVV_k
            for (auto k = 0; k < input.cantComponentes; k++){
                autoCaras[k].autoValor = autoVV[k].autoValor;
                autoCaras[k].autoVector.resize(X.columnas);

                for (auto j = 0; j < X.columnas; j++){
                    double tmp = 0;
                    for (auto i = 0; i < X.filas; i++){
                        tmp += X.datos[i][j] * autoVV[k].autoVector[i];
                    }
                    autoCaras[k].autoVector[j] = tmp;
                }
            }
        } else {
            cout << "Uso: tp2 [--fast]\n\nOpción desconocida.";
            return 1;
        }
    }

    //escribirImagen(vectorAImagen(autoCaras[1].autoVector),
    //               input.ancho,
    //               input.alto,
    //               "autocara2.pgm");

    imprimirVector(
        transformacionCaracteristica(
            autoCaras, input.vTests[0].img));

    return 0;
}
