#include <iostream>
#include <vector>
#include <cstdlib>

#include "utilities.h"

using namespace std;

void levantarDatos(Input& input){
    // Primera linea
    cin >> input.path;
    cin >> input.filas;
    cin >> input.columnas;
    cin >> input.cantPersonas;
    cin >> input.cantImgPorPers;
    cin >> input.cantComponentes;

    // Levanto imagenes de la base
    for(int i = 0; i < input.cantPersonas; i++){
        ImgBase b;
        cin >> b.persona;
        for(int j = 0; j < input.cantImgPorPers; j++){
            int auxImagen;
            cin >> auxImagen;
            b.nroImagen.push_back(auxImagen);
        }
        input.vBase.push_back(b);
    }

    // Imagenes para testear con su numero de test
    cin >> input.nTest;
    for(int i = 0; i < input.nTest; i++){
        ImgTest t;
        cin >> t.path;
        cin >> t.nroTest;
        input.vTests.push_back(t);
    }
}

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

void imprimirMatriz(const matriz& m){
    for (auto i : m){
        for (auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
}

matriz generarMatrizM(const Input& input){
    vector<double> imgProm(input.filas * input.columnas, 0);
    vector< vector<unsigned char> > vImagenesEnChar;
    matriz X;
    matriz M(input.filas*input.columnas, vector<double> (input.filas*input.columnas, 0));

    // levanto todas las imagenes y a medida que lo voy haciendo
    // calculo la suma para la imagen promedio.
    for(int i = 0; i < input.cantPersonas; i++){
        for(int j = 0; j < input.cantImgPorPers; j++){
            vector<unsigned char> vAux = levantarImagen(input.path + input.vBase[i].persona + to_string(input.vBase[i].nroImagen[j]) + ".pgm");
            vImagenesEnChar.push_back(vAux);
            sumarAProm(imgProm, vAux);
        }
    }

    // promedio: u = (x1 +...+ xn)/n
    multiplicarVectorPorEscalar(imgProm, 1 / input.cantPersonas * input.cantImgPorPers);

    // (xi - u)
    for(int i = 0; i < (input.cantPersonas * input.cantImgPorPers); i++){
        vector<double> vAux;
        sumarYAgregarAVector(vAux,vImagenesEnChar[i], imgProm);
        X.push_back(vAux);
    }

    // (xi - u)^t * (xi - u) / (n-1)
    obtenerMatrizM(M, X);

    return M;
}

void sumarAProm(vector<double>& a, const vector<unsigned char>& b){
    // si op == true -> la operacion es suma
    // si op == false -> la operacion es resta
    if(a.size() != b.size()){
        fail("error sumarAProm: No se pueden sumar/restar matrices de tamaños distintos.");
    }

    for(unsigned int i = 0; i < a.size(); i++){
        a[i] += (double)b[i];
    }
}

void multiplicarVectorPorEscalar(vector<double>& v, const double escalar){
    for(unsigned int i = 0; i < v.size(); i++){
            v[i] *= escalar;
    }
}

void sumarYAgregarAVector(vector<double>& v, const vector<unsigned char>& imgChar, const vector<double>& vProm){
    if(imgChar.size() != vProm.size()){
        fail("Tienen tamaños distintos las matrices.");
    }

    for(unsigned int i = 0; i < vProm.size(); i++){
        v.push_back((double)imgChar[i] + vProm[i]);
    }
}

void obtenerMatrizM(matriz& M, const matriz& X){
    double d = 1 / (double)(X.size() -1);
    for(unsigned int i = 0; i < M.size(); i++){
        for(unsigned int j = 0; j < M[i].size(); j++){
            M[i][j] = prodInterno(X, X, i, j, X.size()) * d;
        }
    }    

}

double prodInterno(const matriz& a, const matriz& b, int i, int j, unsigned int size){
    double suma = 0;

    for(unsigned int k = 0; k < size; k++){
        suma += a[k][i] * b[k][j];
    }

    return suma;
}
