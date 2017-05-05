#ifndef LINALG_H
#define LINALG_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "tipos.h"
#include "utilities.h"
#include <cmath>

using namespace std;

double prodInterno(const Matriz& a, const Matriz& b, int i, int j, unsigned int size);
void sumarAProm(vector<double>& a, const vector<unsigned char>& b);
void sumarYAgregarAVector(vector<double>& v, const vector<unsigned char>& imgChar, const vector<double>& vProm);
void multiplicarVectorPorEscalar(vector<double>& a, const double escalar);
AutoValorYVector metodoPotencia(const Matriz& A, const vector<double>& x, int cantIter);
double normaInf(const vector<double>& v);
double normaUno(const vector<double>& v);
double normaDos(const vector<double>& v);

#endif