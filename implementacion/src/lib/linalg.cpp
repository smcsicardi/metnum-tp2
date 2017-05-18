#include "linalg.h"
#include "time.h"

using namespace std;

void vectorPorEscalar(vector<double>& v, double escalar){
    for(unsigned int i = 0; i < v.size(); i++){
        v[i] *= escalar;
    }
}

//void sumarYAgregarAVector(vector<double>& v, const vector<unsigned char>& imgChar, const vector<double>& vProm){
//    if(imgChar.size() != vProm.size()){
//        fail("Tienen tamaños distintos las matrices.");
//    }
//
//    for(unsigned int i = 0; i < vProm.size(); i++){
//        v.push_back((double)imgChar[i] + vProm[i]);
//    }
//}

double prodInternoXtX(const Matriz& a, const Matriz& b, int i, int j, unsigned int size){
    double suma = 0;

    for(unsigned int k = 0; k < size; k++){
        suma += a.datos[k][i] * b.datos[k][j];
    }

    return suma;
}

EigenVV metodoPotencia(const Matriz& B, int cantIter){
    // Genero un vector random para calcular el metodo.
    vector<double> vRand(B.filas, 1);
    // vector<double> vRand;
    // for(int i = 0; i < B.filas; i++){
        // srand((unsigned)time(0));
        // vRand.push_back((double)(rand() % 10000));
        // vRand.push_back(i);
    // }

    for(int i = 0; i < cantIter; i++){
        // Calculo B*v
        vector<double> b = matrizXVector(B, vRand);

        // Lo normalizo
        double norma = 1.00 / normaDos(b);
        vectorPorEscalar(b, norma);
        vRand = b;
    }

    // lambda = v^t * (B * v) / (v^t * v)
    vector<double> Bv = matrizXVector(B, vRand);

    EigenVV e;
    e.autoValor = prodInterno(Bv, vRand) / prodInterno(vRand, vRand);
    e.autoVector = vRand;
    return e;
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
    vector<double> s = v;
    for(auto& val : s){
        val = val*val;
    }
    double suma = kahan(s);

    return sqrt(suma);
}

vector<double> matrizXVector(const Matriz& A, const vector<double>& x){
    vector<double> b (A.filas);

    if((A.filas == 0 && A.columnas == 0) || (A.filas != (int)(x.size()))){
        fail("MatrizXVector: matriz vacia o distintos tamaños entre fila de matriz y vector.");
    }

    for(auto i = 0; i < A.filas; i++){
        b[i] = prodInterno(A.datos[i], x);
    }

    return b;
}

double prodInterno(const vector<double>& v1, const vector<double>& v2){
    if(v1.size() != v2.size()){
        fail("prodInterno: vectores de distintos tamaños");
    }

    double suma = 0;
    for(auto i = 0; i < v1.size(); i++){
        suma += v1[i] * v2[i];
    }

    return suma;
}

void deflacion(Matriz& A, const EigenVV& e){
    int size = e.autoVector.size();
    if(A.filas != size){
        fail("deflacion: La matriz tiene un tamaño de fila distinto del autovector");
    }

    // A - lambda * v * v^t
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            A.datos[i][j] -= e.autoValor * e.autoVector[i] * e.autoVector[j];
        }
    }
}

double kahan(const vector<double>& v){
    double sum = 0.0;
    double c = 0.0;
    for (unsigned int i = 0; i < v.size(); i++){
        double y = v[i] - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

vector<double> reEscalar(const vector<double>& v, double low, double high){
    /* Transforma un vector con números en el rango [min, max]
     * a uno con nros en el rango [low, high].
     */
    auto mm = minmax_element(v.begin(), v.end());

    vector<double> result (v.size());
    for (unsigned int i = 0; i < v.size(); i++){
        result[i] = low + (high - low) * (v[i] - *mm.first)
                                       / (*mm.second - *mm.first);
    }
    return result;
}


vector<EigenVV> obtenerAutoVV(Matriz& M, int cantComponentes){
    // modifica M
    vector<EigenVV> ac(cantComponentes);

    for(auto i = 0; i < cantComponentes; i++){
        // TODO ver criterio de parada
        ac[i] = metodoPotencia(M, 100);
        deflacion(M, ac[i]);
    }

    return ac;
}
