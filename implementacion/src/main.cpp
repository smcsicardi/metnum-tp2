#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <string>

#include "lib/tipos.h"
#include "lib/pgm.h"
#include "lib/utilities.h"
#include "lib/linalg.h"
#include "lib/parser.h"

using namespace std;

int main(int argv, char* argc[]){
    Input input = levantarDatos();
    Matriz M = obtenerMatrizM(input);
    autoCaras ac = obtenerAutoCaras(M, input);
    // imprimirAutoCaras(ac, input.filas, input.columnas);

    imprimirVector(transformacionCaracteristica(ac, input.vTests[0].img));

    return 0;
}
