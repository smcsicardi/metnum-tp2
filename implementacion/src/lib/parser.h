#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "tipos.h"
#include "pgm.h"
#include "linalg.h"

using namespace std;

Input levantarDatos();
Matriz obtenerMatrizM(const Input& input);
Matriz multiplicarXtX(const Matriz& vX);
vector<EigenVV> obtenerAutoCaras(Matriz& M, Input& input);
vector<double> transformacionCaracteristica(const vector<EigenVV>& ac, const imagen& img);

#endif
