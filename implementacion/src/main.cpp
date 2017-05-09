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

    Matriz M = obtenerMatrizM(input);

    int k = input.cantComponentes;
    vector<EigenVV> eigens (k);
    for (auto i = 0; i < k; i++){
        eigens[i] = metodoPotencia(M, 100);
        M = deflacion(M, eigens[i]);
    }

    imagen tmp = vectorAImagen(eigens[0].autoVector);
    escribirImagen(tmp, input.filas, input.columnas, "lol.pgm");

    //vector<double> xi = {1  2, 3};
    //for (auto i = 0; i < k; i++){
    //    cout << prodInterno(eigens[i].autoVector, xi);
    //    cout << endl;
    //}

    // matriz p1 = levantarMatriz("../data/ImagenesCarasRed/s1/2.pgm");
    // matriz p2 = levantarMatriz(input.path + input.vBase[0].persona + to_string(input.vBase[0].nroImagen[0]) + ".pgm");

    // cout << input.path + input.vBase[0].persona + to_string(input.vBase[0].nroImagen[0]) + ".pgm" << endl;

    // imprimirMatriz(p2);

    // matriz x;
    // matriz m(3, vector<double>(3,0));
    // double val = 1;
    // for(int i = 0; i < 5; i++){
    //     vector<double> aux;
    //     for(int j = 0; j < 3; j++){
    //         aux.push_back(val);
    //         val++;
    //     }
    //     x.push_back(aux);
    // }

    // cout << "matriz x" << endl;
    // imprimirMatriz(x);

    // obtenerMatrizM(m,x);

    // cout << endl << "matrix m" << endl;

    // imprimirMatriz(obtenerMatrizM(input));

    // EigenVV e = metodoPotencia(obtenerMatrizM(input), 10000);

    return 0;
}
