#ifndef LINALG_H
#define LINALG_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "tipos.h"
#include "utilities.h"
#include <algorithm>

using namespace std;

vector<double> matrizXVector(const Matriz& A, const vector<double>& x);
double prodInterno(const vector<double>& v1, const vector<double>& v2);
double prodInternoXtX(const Matriz& a, const Matriz& b, int i, int j, unsigned int size);
//void sumarYAgregarAVector(vector<double>& v, const vector<unsigned char>& imgChar, const vector<double>& vProm);
void vectorPorEscalar(vector<double>& v, const double escalar);
EigenVV metodoPotencia(const Matriz& A);
double normaInf(const vector<double>& v);
double normaUno(const vector<double>& v);
double normaDos(const vector<double>& v);
void deflacion(Matriz& A, const EigenVV& e);
double kahan(const vector<double>& v);
vector<double> reEscalar(const vector<double>& v, double start, double end);
vector<EigenVV> obtenerAutoVV(Matriz& M, int cantComponentes);

#endif
