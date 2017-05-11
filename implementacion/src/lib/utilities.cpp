#include <iostream>
#include <vector>
#include <cstdlib>

#include "utilities.h"
#include "pgm.h"
#include <iomanip> // Libreria para el padding

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

void imprimirVector(const vector<double>& v){
    cerr << fixed << setprecision(3);
    for (auto i : v){
        cerr << setfill(' ') << setw(11) << i;
    }
    cout << endl;
}

void imprimirMatriz(const Matriz &A){
    cerr << fixed << setprecision(3);
    for (auto i : A.datos) {
        for (auto j : i) {
            cerr << setfill(' ') << setw(11) << j;
        }
        cerr << endl;
    }
    cerr << endl;
}

void imprimirAutoCaras(const autoCaras& ac, int filas, int columnas){
    for(unsigned int i = 0; i < ac.size(); i++){
        imagen tmp = vectorAImagen(ac[i].autoVector);
        escribirImagen(tmp, filas, columnas, "autoCara"+to_string(i)+".pgm");
    }
}

vector<double> imagenAVectorDouble(const imagen& img){
    vector<double> v(img.size());
    for(unsigned int i = 0; i < img.size(); i++){
        v[i] = (double)img[i];
    }
    return v;
}