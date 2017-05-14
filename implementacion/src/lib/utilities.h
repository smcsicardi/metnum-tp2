#ifndef UTILITIES_H
#define UTILITIES_H

#include "tipos.h"

void imprimirDatos(const Input& input);
void fail(string msg);
void imprimirVector(const vector<double>& v);
void imprimirMatriz(const Matriz &A);
void imprimirAutoCaras(const vector<EigenVV>& eigens, int filas, int columnas);

#endif // UTILITIES_H
