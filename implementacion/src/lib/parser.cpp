#include "parser.h"

using namespace std;


Input levantarDatos(){
    // Primera linea
    Input input;
    cin >> input.path;
    cin >> input.alto;
    cin >> input.ancho;
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
        t.img = levantarImagen(t.path);
        input.vTests.push_back(t);
    }
    return input;
}

Matriz obtenerMatrizX(const Input& input){
    int size = input.alto * input.ancho;
    int cantImagenesTotales = input.cantImgPorPers*input.cantPersonas;
    vector<double> mu (size);
    vector<imagen> imagenes (cantImagenesTotales);
    Matriz X(input.cantImgPorPers * input.cantPersonas, size);

    // levanto todas las imagenes y a medida que lo voy haciendo
    // calculo la suma para la imagen promedio.
    int count = 0;
    for(auto i = 0; i < input.cantPersonas; i++){
        for(auto j = 0; j < input.cantImgPorPers; j++){
            imagenes[count] = levantarImagen(input.path +
                                             input.vBase[i].persona +
                                             to_string(input.vBase[i].nroImagen[j]) +
                                             ".pgm");
            sumarAProm(mu, imagenes[count++]);
        }
    }

    // promedio: u = (x1 +...+ xn)/n
    vectorPorEscalar(mu, 1 / (double)cantImagenesTotales);

    // (xi - u)
    for(auto i = 0; i < cantImagenesTotales; i++){
        for (auto j = 0; j < size; j++) {
            X.datos[i][j] = (double)imagenes[i][j] - mu[j];
        }
    }

    return X;
}

Matriz multiplicarXtX(const Matriz& X){
    Matriz M (X.columnas, X.columnas);
    double d = 1 / (double)(X.filas - 1);

    for(auto i = 0; i < X.columnas; i++){
        for(auto j = 0; j < X.columnas; j++){
            M.datos[i][j] = prodInternoXtX(X, X, i, j, X.filas) * d;
        }
    }

    return M;
}

Matriz multiplicarXXt(const Matriz& X){
    Matriz M (X.filas, X.filas);
    double d = 1 / (double)(X.filas - 1);

    for(auto i = 0; i < X.filas; i++){
        for(auto j = 0; j < X.filas; j++){
            double suma = 0;
            for(auto k = 0; k < X.columnas; k++){
                suma += X.datos[i][k] * X.datos[j][k];
            }
            M.datos[i][j] = suma * d;
        }
    }

    return M;
}

vector<EigenVV> obtenerAutoCaras(Matriz& M, Input& input){
    // modifica M
    vector<EigenVV> ac(input.cantComponentes);

    for(auto i = 0; i < input.cantComponentes; i++){
        ac[i] = metodoPotencia(M, 100);
        deflacion(M, ac[i]);
    }

    return ac;
}

vector<double> transformacionCaracteristica(const vector<EigenVV>& ac, const imagen& img){
    vector<double> tc (ac.size());
    vector<double> imgDouble (img.begin(), img.end());

    for(auto i = 0; i < ac.size(); i++){
        tc[i] = prodInterno(ac[i].autoVector, imgDouble);
    }

    return tc;
}
