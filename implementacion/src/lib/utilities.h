#ifndef UTILITIES_H
#define UTILITIES_H

#include "tipos.h"
#include "pgm_reader.h"

void levantarDatos(Input& input);
void imprimirDatos(const Input& input);
void imprimirMatriz(const Matriz& m);

double prodInterno(const Matriz& a, const Matriz& b, int i, int j, unsigned int size);
void sumarAProm(vector<double>& a, const vector<unsigned char>& b);
void sumarYAgregarAVector(vector<double>& v, const vector<unsigned char>& imgChar, const vector<double>& vProm);
void multiplicarVectorPorEscalar(vector<double>& a, const double escalar);
Matriz obtenerMatrizM(const Matriz& vX);

Matriz generarMatrizM(const Input& input, int persona);

#endif // UTILITIES_H
