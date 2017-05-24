#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <chrono>

#include "lib/tipos.h"
#include "lib/pgm.h"
#include "lib/utilities.h"
#include "lib/linalg.h"
#include "lib/parser.h"
#include "lib/knn.h"

#define RELOJ           chrono::high_resolution_clock::now

using namespace std;

int main(int argc, char* argv[]){

    if(argc != 2){
        fail("Se agrega de parametro la cantidad de corridas solamente.");
    }

    int cantCorridas = atoi(argv[1]);

    Input input = levantarDatos();
    vector<double> mu (input.alto * input.ancho, 0);
    Matriz X = obtenerMatrizX(input, mu);

    /*
     * EN ESTE TEST GENERO LAS DOS MATRICES M Y M-MOÑO CON LOS AUTOVALORES Y AUTOVECTORES,
     * LUEGO DEVUELVO DEVUELVO POR SALIDA ESTANDAR LA CANTIDAD DE COMPONENTES,
     * EL PROMEDIO DEL TIEMPO QUE TARDA CON M Y EL PROMEDIO DEL TIEMPO DE M-MOÑO
     */

    double promedioM = 0;
    double promedioMMonio = 0;

    // CALCULO TIEMPO M
    
    for(int i = 0; i < cantCorridas; i++){
        // sin argumentos hace Xt*X
        auto inicio = RELOJ();
        Matriz M = multiplicarXtX(X);
        vector<EigenVV> autoCaras = obtenerAutoVV(M, input.cantComponentes);
        auto fin = RELOJ();

        promedioM += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
    }

    // CALCULO TIEMPO M-MOÑO

    // XXX indefinido si --fast y cantComponentes > cantImagenesTotales
    vector<EigenVV> autoCaras (input.cantComponentes);
    for(int i = 0; i < cantCorridas; i++){
        auto inicio = RELOJ();

        // con --fast hace X*Xt y después Xt*autoVV
        Matriz M_Monio = multiplicarXXt(X);
        vector<EigenVV> autoVV = obtenerAutoVV(M_Monio, input.cantComponentes);

        // autoCaras_k = Xt*autoVV_k
        for (auto k = 0; k < input.cantComponentes; k++){
            autoCaras[k].autoValor = autoVV[k].autoValor;
            autoCaras[k].autoVector.resize(X.columnas);

            for (auto j = 0; j < X.columnas; j++){
                double tmp = 0;
                for (auto i = 0; i < X.filas; i++){
                    tmp += X.datos[i][j] * autoVV[k].autoVector[i];
                }
                autoCaras[k].autoVector[j] = tmp;
            }
        }
        auto fin = RELOJ();

        promedioMMonio += (double) chrono::duration_cast<std::chrono::nanoseconds>(fin-inicio).count();
    }

    cout << input.cantPersonas << "," << input.cantComponentes << ",";
    cout << promedioM / (double) cantCorridas << "," << promedioMMonio / (double) cantCorridas << endl;

    return 0;
}
