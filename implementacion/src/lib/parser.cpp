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

    input.vBase.resize(input.cantPersonas);

    // Levanto imagenes de la base
    for(int i = 0; i < input.cantPersonas; i++){
        ImgBase b;
        b.nrosImagen.resize(input.cantImgPorPers);
        cin >> b.persona;
        for(int j = 0; j < input.cantImgPorPers; j++){
            int auxImagen;
            cin >> auxImagen;
            b.nrosImagen[j] = auxImagen;
        }
        input.vBase[i] = b;
    }

    // Imagenes para testear con su numero de persona
    cin >> input.nTest;
    for(int i = 0; i < input.nTest; i++){
        ImgTest t;
        cin >> t.path;
        cin >> t.persona;
        t.img = levantarImagen(t.path);
        input.vTests.push_back(t);
    }
    return input;
}

Matriz obtenerMatrizX(const Input& input, vector<double>& mu){
    // modifica mu
    int size = input.alto * input.ancho;
    int cantImagenesTotales = input.cantImgPorPers * input.cantPersonas;
    vector<imagen> imagenes (cantImagenesTotales);
    Matriz X (cantImagenesTotales, size);

    // levanto todas las imagenes y a medida que lo voy haciendo
    // calculo la suma para la imagen promedio.

    int n = 0;
    for(auto i = 0; i < input.cantPersonas; i++){
        for(auto j = 0; j < input.cantImgPorPers; j++){
            imagenes[n] = levantarImagen(input.path +
                                         input.vBase[i].persona +
                                         to_string(input.vBase[i].nrosImagen[j]) +
                                         ".pgm");
            for (auto k = 0; k < size; k++){
                mu[k] += (double)imagenes[n][k];
            }
            n++;
        }
    }
    vectorPorEscalar(mu, 1 / (double)cantImagenesTotales);

    // (xi - u) / sqrt(n - 1)
    for(auto i = 0; i < cantImagenesTotales; i++){
        for (auto j = 0; j < size; j++) {
            X.datos[i][j] = ((double)imagenes[i][j] - mu[j])
                            / sqrt(cantImagenesTotales - 1);
        }
    }

    return X;
}

Matriz multiplicarXtX(const Matriz& X){
    Matriz M (X.columnas, X.columnas);

    for(auto i = 0; i < X.columnas; i++){
        for(auto j = 0; j < X.columnas; j++){
            M.datos[i][j] = prodInternoXtX(X, X, i, j, X.filas);
        }
    }

    return M;
}

Matriz multiplicarXXt(const Matriz& X){
    Matriz M (X.filas, X.filas);

    for(auto i = 0; i < X.filas; i++){
        for(auto j = 0; j < X.filas; j++){
            double suma = 0;
            for(auto k = 0; k < X.columnas; k++){
                suma += X.datos[i][k] * X.datos[j][k];
            }
            M.datos[i][j] = suma;
        }
    }

    return M;
}

vector<double> transformacionCaracteristica(const vector<EigenVV>& ac,
                                            const vector<double>& x){
    vector<double> tc (ac.size());

    for(unsigned int i = 0; i < ac.size(); i++){
        tc[i] = prodInterno(ac[i].autoVector, x);
    }

    return tc;
}
