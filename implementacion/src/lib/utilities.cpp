#include <iostream>
#include <vector>
#include <cstdlib>

#include "utilities.h"

using namespace std;


void imprimirDatos(const Input& input){
    cout << input.path << " " << input.filas << " " << input.columnas << " " << input.cantPersonas << " " << input.cantImgPorPers << " " << input.cantComponentes << endl;

    for(auto b : input.vBase){
        cout << b.persona << " " << b.nroImagen.size() << " ";
        for(int j = 0; j < input.cantImgPorPers; j++){
            cout << b.nroImagen[j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << input.nTest << endl;

    for(auto t : input.vTests){
        cout << t.path << " " << t.nroTest << endl;
    }
}

void fail(string msg){
    cerr << msg << endl;
    exit(1);
}

void imprimirMatriz(const Matriz& m){
    for (auto i : m.datos){
        for (auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
}

