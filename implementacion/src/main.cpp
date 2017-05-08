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
    // Input input;

    // levantarDatos(input);
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
    
    // imprimirMatriz(obtenerMatrizM(input));

    // EigenVV e = metodoPotencia(obtenerMatrizM(input), 10000);
    
    Matriz A(3,3);

    A.datos[0][0] = 5;
    A.datos[0][1] = 3;
    A.datos[0][2] = 3;
    A.datos[1][0] = 3;
    A.datos[1][1] = 1;
    A.datos[1][2] = 0;
    A.datos[2][0] = 3;
    A.datos[2][1] = 0;
    A.datos[2][2] = 1;

    Matriz A2(3,3);

    A2.datos[0][0] = 1;
    A2.datos[0][1] = 0;
    A2.datos[0][2] = 2;

    A2.datos[1][0] = 0;
    A2.datos[1][1] = 1;
    A2.datos[1][2] = 0;
    
    A2.datos[2][0] = 2;
    A2.datos[2][1] = 0;
    A2.datos[2][2] = 1;

    cout << "imprimo matriz A2" << endl;
    imprimirMatriz(A2);

    EigenVV e1 = metodoPotencia(A2, 10000);

    cout << endl << "auto valor = " << e1.autoValor << endl;
    cout << "auto vector = ";
    imprimirVector(e1.autoVector);

    cout << endl;

    cout << "imprimo matriz B" << endl;
    Matriz B = deflacion(A2, e1);
    imprimirMatriz(B);

    EigenVV e2 = metodoPotencia(B, 10000);
    cout << endl << "auto valor = " << e2.autoValor << endl;
    cout << "auto vector = ";
    imprimirVector(e2.autoVector);

    cout << endl;

    cout << "imprimo matriz C" << endl;
    Matriz C = deflacion(B, e2);
    imprimirMatriz(C);

    EigenVV e3 = metodoPotencia(C, 10000);
    cout << endl << "auto valor = " << e3.autoValor << endl;
    cout << "auto vector = ";
    imprimirVector(e3.autoVector);

    return 0;
}
