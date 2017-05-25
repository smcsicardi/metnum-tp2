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
    /*
     * Toma el mismo stdin que ./tp2  mas el k de kNN
     * y genera datos de la clasificación.
     */

    Input input = levantarDatos();
    int cantImagenesTotales = input.cantImgPorPers * input.cantPersonas;
    vector<double> mu (input.alto * input.ancho, 0);
    Matriz X = obtenerMatrizX(input, mu);
    vector<EigenVV> autoCaras (input.cantComponentes);
    Matriz M = multiplicarXXt(X);
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

    // X2 tiene los datos originales transformados y clasificados
    // X2 = [ Punto< tc(x_i), nro persona > ]
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


    // guardo X2 como persona,x1,x2,...,xn
    guardarCSV(X2, input.cantComponentes, "csv/X2.csv");

    // para cada vTest, clasifico con kNN
    for (auto t : input.vTests){
        vector<double> y (input.alto * input.ancho);

        // y = (img - mu) / sqrt(n - 1)
        for(auto i = 0; i < y.size(); i++){
            y[i] = ((double)t.img[i] - mu[i])
                   / sqrt(cantImagenesTotales - 1);
        }

        Punto p (t.persona,
                 transformacionCaracteristica(autoCaras, y));
        cout << p.coordenadas.size() << endl;
        for (int i = 0; i < p.coordenadas.size(); ++i)
        {
            cout << p.coordenadas[i] << endl;
        }
    }
}
