#ifndef TIPOS_H
#define TIPOS_H

#include <vector>

using namespace std;

#define matriz vector<vector<int>>

struct ImgBase{

    ImgBase(){
    }

    string persona;
    vector<int> nroImagen;
};

struct ImgTest{
    ImgTest(){
    }

    string path;
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

#endif
