#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "tipos.h"
#include "pgm_reader.h"
#include "linalg.h"

using namespace std;

void levantarDatos(Input& input);
Matriz obtenerMatrizM(const Input& input, int persona);
Matriz multiplicarXtX(const Matriz& vX);
MatricesM obtenerTodasMatricesM(const Input& input);

#endif