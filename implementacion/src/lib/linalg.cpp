#include "linalg.h"

using namespace std;

void sumarAProm(vector<double>& a, const imagen& b){
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

double prodInternoXtX(const Matriz& a, const Matriz& b, int i, int j, unsigned int size){
    double suma = 0;

    for(unsigned int k = 0; k < size; k++){
        suma += a.datos[k][i] * b.datos[k][j];
    }

    return suma;
}

EigenVV metodoPotencia(const Matriz& A, int cantIter){
    EigenVV eigen;

    // Genero un vector random para calcular el metodo.
    vector<double> vRand;
    for(int i = 0; i < A.filas; i++){
        vRand.push_back(rand() % 100);
    }

    for(int i = 0; i < cantIter; i++){
        // Calculo A*v
        vector<double> b = matrizXVector(A,vRand);

        // Lo normalizo
        double norma = 1 / normaDos(b);
        multiplicarVectorPorEscalar(b,norma);    
        vRand = b;
    }

    // lambda = v^t * (A * v) / (v^t * v)
    vector<double> Av = matrizXVector(A,vRand);
    eigen.autoValor = prodInterno(Av, vRand) / prodInterno(vRand, vRand);
    eigen.autoVector = vRand;

    return eigen;
}

double normaInf(const vector<double>& v){
    double suma = 0;

    for(auto val : v){
        suma = abs(val) > suma ? abs(val) : suma;
    }

    return suma;
}

double normaUno(const vector<double>& v){
    double suma = 0;

    for(auto val : v){
        suma += abs(val);
    }

    return suma;
}

double normaDos(const vector<double>& v){
    double suma = 0;

    for(auto val : v){
        suma += val*val;
    }
    sqrt(suma);

    return suma;
}

vector<double> matrizXVector(const Matriz& A, const vector<double>& x){
    vector<double> b;

    if((A.filas == 0 && A.columnas == 0) || (A.filas != (int)(x.size()))){
        fail("MatrizXVector: matriz vacia o distintos tamaños entre fila de matriz y vector.");
    }

    for(auto m : A.datos){
        b.push_back(prodInterno(m, x));
    }

    return b;
}

double prodInterno(const vector<double>& v1, const vector<double>& v2){
    double suma = 0;
    if(v1.size() != v2.size()){
        fail("prodInterno: vectores de distintos tamaños");
    }

    for(unsigned int i = 0; i < v1.size(); i++){
        suma += v1[i] * v2[i];
    }

    return suma;
}