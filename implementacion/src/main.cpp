#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <string>

#include "lib/tipos.h"
#include "lib/pgm_reader.h"
#include "lib/utilities.h"
#include "lib/linalg.h"
#include "lib/parser.h"

using namespace std;

int main(int argv, char* argc[]){
    Input input;

    levantarDatos(input);
    // imprimirDatos(input);

    // matriz M = generarMatrizM(input);

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
    
    // imprimirMatriz(obtenerMatrizM(input, 0));

    MatricesM mm = obtenerTodasMatricesM(input);
    cout << "cantidad de matrices M = " << mm.vM.size() << endl;

    EigenVV e = metodoPotencia(mm.vM[0], 100);

    cout << endl << "auto valor = " << e.autoValor << endl;
    cout << "auto vector = ";
    imprimirVector(e.autoVector);

    return 0;
}
