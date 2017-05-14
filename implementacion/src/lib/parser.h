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
Matriz obtenerMatrizX(const Input& input);
Matriz multiplicarXtX(const Matriz& X);
Matriz multiplicarXXt(const Matriz& X);
vector<EigenVV> obtenerAutoCaras(Matriz& M, Input& input);
vector<double> transformacionCaracteristica(const vector<EigenVV>& ac, const imagen& img);

#endif
