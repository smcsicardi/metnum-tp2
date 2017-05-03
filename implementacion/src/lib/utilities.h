#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream> // cout, cerr
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct ImgBase{

    ImgBase(){
    }

    string persona;
    vector<int> nroImagen;
};

struct ImgTest{
    ImgTest(){
    }

    string path; // el numero es arbitrario
    int nroTest;
};

struct Input{
    Input(){
    }

    string path;
    int filas;
    int columnas;
    int cantPersonas;
    int cantImgPorPers;
    int cantComponentes;
    int nTest;
    vector<ImgBase> vBase;
    vector<ImgTest> vTests;
};

void levantarDatos(Input& input);
void imprimirDatos(const Input& input);

#endif // UTILITIES_H