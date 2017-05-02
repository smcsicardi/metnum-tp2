#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <math.h>
#include <vector>
#include <iomanip> // Libreria para el padding

using namespace std;


struct ImgBase{

    ImgBase(){
    }

    char carpeta[10]; // el numero es arbitrario
    vector<int> nroImagen;
};

struct ImgTest{
    ImgTest(){
    }

    char path[50]; // el numero es arbitrario
    int nroTest;
};


int main(int argv, char* argc[]){
    char path[50];  // el numero es arbitrario, no encontre otra forma
    int filas;
    int columnas;
    int cantPersonas;
    int cantImgPorPers;
    int cantComponentes;
    int auxImagen;
    int nTest;

    // Primera linea
    cin >> path;
    cin >> filas;
    cin >> columnas;
    cin >> cantPersonas;
    cin >> cantImgPorPers;
    cin >> cantComponentes;

    // Levanto imagenes de la base
    ImgBase arregloBase[cantPersonas];

    for(int i = 0; i < cantPersonas; i++){
        cin >> arregloBase[i].carpeta;
        for(int j = 0; j < cantImgPorPers; j++){
            cin >> auxImagen;
            arregloBase[i].nroImagen.push_back(auxImagen);
        }
    }

    // Imagenes para testear
    cin >> nTest;
    ImgTest arregloTests[nTest];
    for(int i = 0; i < nTest; i++){
        cin >> arregloTests[i].path;
        cin >> arregloTests[i].nroTest;
    }


    cout << endl << path << " " << filas << " " << columnas << " " << cantPersonas << " " << cantImgPorPers << " " << cantComponentes << endl;

    cout << endl << endl;

    for(int i = 0; i < cantPersonas; i++){
        cout << arregloBase[i].carpeta << " " << arregloBase[i].nroImagen.size() << " ";
        for(int j = 0; j < cantImgPorPers; j++){
            cout << arregloBase[i].nroImagen[j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << nTest << endl;

    for(int i = 0; i < nTest; i++){
        cout << arregloTests[i].path << " " << arregloTests[i].nroTest << endl;
    }

    cout << endl;

    // FILE *imagen;
    // imagen = fopen("../data/ImagenesCaras/s1/1.pgm", "r+");

    return 0;
}