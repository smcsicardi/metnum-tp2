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

void imprimirMatriz(const Matriz& m){
    for (auto i : m.datos){
        for (auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }
}

Matriz generarMatrizM(const Input& input, int persona){
    int size = input.filas * input.columnas;
    vector<double> mu (size);
    vector<imagen> imagenes (input.cantImgPorPers);
    Matriz X(input.cantImgPorPers, size);
    ImgBase base = input.vBase[persona];

    // levanto todas las imagenes y a medida que lo voy haciendo
    // calculo la suma para la imagen promedio.
    for(auto j = 0; j < input.cantImgPorPers; j++){
        imagenes[j] = levantarImagen(input.path + base.persona + to_string(base.nroImagen[j]) + ".pgm");
        sumarAProm(mu, imagenes[j]);
    }

    // promedio: u = (x1 +...+ xn)/n
    multiplicarVectorPorEscalar(mu, 1 / input.cantImgPorPers);

    // (xi - u)
    for(auto i = 0; i < input.cantImgPorPers; i++){
        for (auto j = 0; j < size; j++) {
            X.datos[i][j] = imagenes[i][j] - mu[j];
        }
    }

    // (xi - u)^t * (xi - u) / (n-1)
    Matriz M = obtenerMatrizM(X);

    return M;
}

void sumarAProm(vector<double>& a, const imagen& b){
    // si op == true -> la operacion es suma
    // si op == false -> la operacion es resta
    if(a.size() != b.size()){
        fail("error sumarAProm: No se pueden sumar/restar matrices de tamaños distintos.");
    }

    for(auto i = 0; i < a.size(); i++){
        a[i] += (double)b[i];
    }
}

void multiplicarVectorPorEscalar(vector<double>& v, const double escalar){
    for(auto i = 0; i < v.size(); i++){
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

Matriz obtenerMatrizM(const Matriz& X){
    double d = 1 / (double)(X.filas);

    Matriz M(X.columnas, X.columnas);

    for(auto i = 0; i < X.columnas; i++){
        for(auto j = 0; j < X.columnas; j++){
            M.datos[i][j] = prodInterno(X, X, i, j, X.filas) * d;
        }
    }

    return M;
}

double prodInterno(const Matriz& a, const Matriz& b, int i, int j, unsigned int size){
    double suma = 0;

    for(auto k = 0; k < size; k++){
        suma += a.datos[k][i] * b.datos[k][j];
    }

    return suma;
}
