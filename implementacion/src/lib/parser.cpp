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

Matriz obtenerMatrizM(const Input& input){
    int size = input.filas * input.columnas;
    int cantImagenesTotales = input.cantImgPorPers*input.cantPersonas;
    vector<double> mu (size);
    vector<imagen> imagenes (cantImagenesTotales);
    Matriz X(input.cantImgPorPers * input.cantPersonas, size);

    // levanto todas las imagenes y a medida que lo voy haciendo
    // calculo la suma para la imagen promedio.
    int count = 0;
    for(auto i = 0; i < input.cantPersonas; i++){
        for(auto j = 0; j < input.cantImgPorPers; j++){
            imagenes[count] = levantarImagen(input.path + input.vBase[i].persona + to_string(input.vBase[i].nroImagen[j]) + ".pgm");
            sumarAProm(mu, imagenes[count++]);
        }
    }

    cout << "imprimir u" << endl;
    imprimirVector(mu);

    // promedio: u = (x1 +...+ xn)/n
    multiplicarVectorPorEscalar(mu, 1 / (double)cantImagenesTotales);

    cout << "imprimir u" << endl;
    imprimirVector(mu);    

    // (xi - u)
    for(auto i = 0; i < cantImagenesTotales; i++){
        for (auto j = 0; j < size; j++) {
            X.datos[i][j] = (double)imagenes[i][j] - mu[j];
        }
    }

    // (xi - u)^t * (xi - u) / (n-1)
    Matriz M = multiplicarXtX(X);

    return M;
}

Matriz multiplicarXtX(const Matriz& X){
    Matriz M(X.columnas, X.columnas);
    double d = 1 / (double)(X.filas - 1);

    for(auto i = 0; i < X.columnas; i++){
        for(auto j = 0; j < X.columnas; j++){
            M.datos[i][j] = prodInternoXtX(X, X, i, j, X.filas) * d;
        }
    }

    return M;
}