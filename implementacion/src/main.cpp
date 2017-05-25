#include <iostream>
#include <cstdlib>
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
    //int cantImagenesTotales = input.cantImgPorPers * input.cantPersonas;
    vector<double> mu (input.alto * input.ancho, 0);
    Matriz X = obtenerMatrizX(input, mu);

    // XXX indefinido si --fast y cantComponentes > cantImagenesTotales
    vector<EigenVV> autoCaras (input.cantComponentes);
    Matriz M;

    if (argc <= 1) {
        // sin argumentos hace Xt*X
        M = multiplicarXtX(X);
        autoCaras = obtenerAutoVV(M, input.cantComponentes);
    } else if (string(argv[1]) == "--fast"){
        // con --fast hace X*Xt y después Xt*autoVV
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
        cerr << "Uso: tp2 [--fast]\n";
        return 1;
    }

    // normalizo autoCaras y las guardo en eigenfaces/
    for (auto i = 0u; i < autoCaras.size(); i++){
        auto& ac = autoCaras[i];
        vectorPorEscalar(ac.autoVector, 1 / normaDos(ac.autoVector));

        escribirImagen(vectorAImagen(ac.autoVector),
                       input.ancho,
                       input.alto,
                       "eigenfaces/autocara" + to_string(i) + ".pgm");
    }

    // print componentes principales
    for (auto ac : autoCaras){
        cout << sqrt(ac.autoValor) << endl;
    }

    return 0;
}
