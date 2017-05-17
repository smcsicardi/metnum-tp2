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
#include "lib/knn.h"

using namespace std;

int main(int argc, char* argv[]){
    Input input = levantarDatos();
    int cantImagenesTotales = input.cantImgPorPers * input.cantPersonas;
    vector<double> mu (input.alto * input.ancho, 0);
    Matriz X = obtenerMatrizX(input, mu);

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

    // X2 = [ Punto( tc(x_i) , nro persona ) ]
    vector<Punto> X2 (cantImagenesTotales);

    int n = 0;
    for (auto p = 0; p < input.cantPersonas; p++){
        for (auto i = 0; i < input.cantImgPorPers; i++){
            X2[n].persona = p + 1;
            X2[n].coordenadas = transformacionCaracteristica(
                    autoCaras, X.datos[n]);
            n++;
        }
    }

    Punto p;
    p.persona = input.vTests[1].persona;
    vector<double> y (input.alto * input.ancho);
    // y = (img - mu) / sqrt(n - 1)
    for(auto i = 0; i < y.size(); i++){
        y[i] = ((double)input.vTests[1].img[i] - mu[i])
               / sqrt(cantImagenesTotales - 1);
    }
    p.coordenadas = transformacionCaracteristica(autoCaras, y);
    int k = (input.cantPersonas % 2 == 0) ? 5 : 6;
    cout << "persona: " << kNN(X2, p, k, input.cantPersonas) << endl;

    //escribirImagen(vectorAImagen(autoCaras[1].autoVector),
    //               input.ancho,
    //               input.alto,
    //               "autocara2.pgm");

    return 0;
}
