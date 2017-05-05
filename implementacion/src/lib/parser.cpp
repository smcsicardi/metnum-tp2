#include "parser.h"

using namespace std;


void levantarDatos(Input& input){
    // Primera linea
    cin >> input.path;
    cin >> input.filas;
    cin >> input.columnas;
    cin >> input.cantPersonas;
    cin >> input.cantImgPorPers;
    cin >> input.cantComponentes;

    // Levanto imagenes de la base
    for(int i = 0; i < input.cantPersonas; i++){
        ImgBase b;
        cin >> b.persona;
        for(int j = 0; j < input.cantImgPorPers; j++){
            int auxImagen;
            cin >> auxImagen;
            b.nroImagen.push_back(auxImagen);
        }
        input.vBase.push_back(b);
    }

    // Imagenes para testear con su numero de test
    cin >> input.nTest;
    for(int i = 0; i < input.nTest; i++){
        ImgTest t;
        cin >> t.path;
        cin >> t.nroTest;
        input.vTests.push_back(t);
    }
}

Matriz obtenerMatrizM(const Input& input, int persona){
    int size = input.filas * input.columnas;
    vector<double> mu (size);
    vector<imagen> imagenes (input.cantImgPorPers);
    Matriz X(input.cantImgPorPers, size);
    ImgBase base = input.vBase[persona];

    // levanto todas las imagenes y a medida que lo voy haciendo
    // calculo la suma para la imagen promedio.
    for(auto j = 0; j < input.cantImgPorPers; j++){
        imagenes[j] = levantarImagen(input.path + base.persona + to_string(base.nroImagen[j]) + ".pgm");
        sumarAProm(mu, imagenes[j]);
    }

    // promedio: u = (x1 +...+ xn)/n
    multiplicarVectorPorEscalar(mu, 1 / (double)input.cantImgPorPers);

    // (xi - u)
    for(auto i = 0; i < input.cantImgPorPers; i++){
        for (auto j = 0; j < size; j++) {
            X.datos[i][j] = imagenes[i][j] - mu[j];
        }
    }

    // (xi - u)^t * (xi - u) / (n-1)
    Matriz M = multiplicarXtX(X);

    return M;
}

Matriz multiplicarXtX(const Matriz& X){
    Matriz M(X.columnas, X.columnas);
    double d = 1 / (double)(X.filas);

    for(auto i = 0; i < X.columnas; i++){
        for(auto j = 0; j < X.columnas; j++){
            M.datos[i][j] = prodInternoXtX(X, X, i, j, X.filas) * d;
        }
    }

    return M;
}

MatricesM obtenerTodasMatricesM(const Input& input){
    MatricesM mm;

    for(int i = 0; i < input.cantPersonas; i++){
        mm.vM.push_back(obtenerMatrizM(input, i));
    }

    return mm;
}
