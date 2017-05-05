#ifndef TIPOS_H
#define TIPOS_H

#include <vector>

using namespace std;

#define imagen vector<unsigned char>

struct Matriz{
    int filas;
    int columnas;
    vector<vector<double>> datos;

    Matriz(int filas, int columnas){
        this->filas = filas;
        this->columnas = columnas;
        this->datos = vector<vector<double>> (filas, vector<double> (columnas));
    }

    Matriz operator+(const Matriz& other) const
    {
        Matriz c = Matriz(this->filas, this->columnas);

        for (auto i = 0; i < this->filas; i++) {
            for (auto j = 0; j < this->columnas; j++) {
                c.datos[i][j] = this->datos[i][j] + other.datos[i][j];
            }
        }

        return c;
    }

    Matriz operator-(const Matriz& other) const
    {
        Matriz c = Matriz(this->filas, this->columnas);

        for (auto i = 0; i < this->filas; i++) {
            for (auto j = 0; j < this->columnas; j++) {
                c.datos[i][j] = this->datos[i][j] - other.datos[i][j];
            }
        }

        return c;
    }

    void operator=(const Matriz& other){
        this->filas = other.filas;
        this->columnas = other.columnas;
        this->datos = other.datos;
    }

};

struct ImgBase{
    string persona;
    vector<int> nroImagen;
};

struct ImgTest{
    string path;
    int nroTest;
};

struct Input{
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

struct MatricesM{
    vector<Matriz> vM;
};

struct EigenVV{
    EigenVV(){
        this->autoValor = -1.00;
    }
    double autoValor;
    vector<double> autoVector;
};

#endif
