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

    if (argc != 2){
        cerr << "Uso: kfold k-nearest-neightbours\n";
        return 1;
    }

    int k = atoi(argv[1]);

    Input input = levantarDatos();
    int cantImagenesTotales = input.cantImgPorPers * input.cantPersonas;
    vector<double> mu (input.alto * input.ancho, 0);
    Matriz X = obtenerMatrizX(input, mu);

    Matriz M = multiplicarXtX(X);
    vector<EigenVV> autoCaras = obtenerAutoVV(M, input.cantComponentes);

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

        // k es par si cantPersonas impar, y viceversa
        int p_class = kNN(X2, p, k, input.cantPersonas);
        cout << "persona " << t.persona << " -> "
             << p_class << endl;
    }
}
