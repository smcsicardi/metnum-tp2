#ifndef LINALG_H
#define LINALG_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "tipos.h"
#include "utilities.h"

using namespace std;

double prodInterno(const Matriz& a, const Matriz& b, int i, int j, unsigned int size);
void sumarAProm(vector<double>& a, const vector<unsigned char>& b);
void sumarYAgregarAVector(vector<double>& v, const vector<unsigned char>& imgChar, const vector<double>& vProm);
void multiplicarVectorPorEscalar(vector<double>& a, const double escalar);

#endif