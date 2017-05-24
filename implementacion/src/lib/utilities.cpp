#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>

#include "utilities.h"
#include "pgm.h"
#include <iomanip> // Libreria para el padding

using namespace std;


void imprimirDatos(const Input& input){
    cout << input.path << " " << input.alto << " " << input.ancho << " " << input.cantPersonas << " " << input.cantImgPorPers << " " << input.cantComponentes << endl;

    for(auto b : input.vBase){
        cout << b.persona << " " << b.nrosImagen.size() << " ";
        for(int j = 0; j < input.cantImgPorPers; j++){
            cout << b.nrosImagen[j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << input.nTest << endl;

    for(auto t : input.vTests){
        cout << t.path << " " << t.persona << endl;
    }
}

void fail(string msg){
    cerr << msg << endl;
    exit(1);
}

void imprimirVector(const vector<double>& v){
    cerr << fixed << setprecision(3);
    for (auto i : v){
        cerr << i << ", ";
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

void imprimirAutoCaras(const vector<EigenVV>& ac, int filas, int columnas){
    for(unsigned int i = 0; i < ac.size(); i++){
        imagen tmp = vectorAImagen(ac[i].autoVector);
        escribirImagen(tmp, filas, columnas, "autoCara"+to_string(i)+".pgm");
    }
}

void guardarCSV(const vector<Punto>& X, int dimension, string path){
    ofstream outfile (path);

    // escribo el header
    outfile << "persona,";
    for (auto j = 1; j <= dimension; j++){
        outfile << "x" << j << (j < dimension ? "," : "");
    }
    outfile << endl;

    // y cada fila
    for (unsigned int i = 0; i < X.size(); i++){
        outfile << X[i].persona << ",";
        for (auto j = 1; j <= dimension; j++){
            outfile << X[i].coordenadas[j]
                    << (j < dimension ? "," : "");
        }
        outfile << endl;
    }
}
