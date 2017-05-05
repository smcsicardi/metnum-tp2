#ifndef UTILITIES_H
#define UTILITIES_H

#include "tipos.h"
#include "pgm_reader.h"

void levantarDatos(Input& input);
void imprimirDatos(const Input& input);
void fail(string msg);
void imprimirMatriz(const matriz& m);

double prodInterno(const matriz& a, const matriz& b, int i, int j, unsigned int size);
void sumarAProm(vector<double>& a, const vector<unsigned char>& b);
void sumarYAgregarAVector(vector<double>& v, const vector<unsigned char>& imgChar, const vector<double>& vProm);
void multiplicarVectorPorEscalar(vector<double>& a, const double escalar);
void obtenerMatrizM(matriz& M, const matriz& vX);

matriz generarMatrizM(const Input& input);

#endif // UTILITIES_H
