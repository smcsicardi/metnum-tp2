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

double prodInterno(const Matriz& a, const Matriz& b, int i, int j, unsigned int size){
    double suma = 0;

    for(unsigned int k = 0; k < size; k++){
        suma += a.datos[k][i] * b.datos[k][j];
    }

    return suma;
}

AutoValorYVector metodoPotencia(const Matriz& A, const vector<double>& x, int cantIter){
    AutoValorYVector lambdaVector;

    // for(int i = 0; i < cantIter; i++){

    // }

    return lambdaVector;
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
