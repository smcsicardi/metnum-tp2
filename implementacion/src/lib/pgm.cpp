#include <iostream>
#include <fstream>
#include <limits>

#include "linalg.h"
#include "tipos.h"
#include "utilities.h"
#include "pgm.h"

using namespace std;

imagen levantarImagen(string path){
    /* Parseando PGM de acuerdo a
     * http://netpbm.sourceforge.net/doc/pgm.html
     */
    ifstream infile (path, ios::binary);

    if (!infile.is_open()) {
        fail("Unable to open file: \"" + path + "\".");
    }

    // los 4 valores que tiene el header: [version, w, h, maxVal]
    vector<string> vals (4);
    int count = 0;
    while (count < 4) {
        // leemos en un buffer
        string buff;
        infile >> buff;
        if (buff.compare(0, 1, "#") == 0) {
            // si encontré un #, ignoro hasta newline
            infile.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            // si no, es un valor a guardar
            vals[count] = buff;
            count += 1;
        }
    }
    // finalmente ignoro el último newline
    infile.ignore(numeric_limits<streamsize>::max(), '\n');

    string version = vals[0];
    int width = stoi(vals[1]);
    int height = stoi(vals[2]);

    if(version.compare("P5") != 0){
        fail("No es P5");
    }

    imagen imgData (height * width);

    // asumo maxVal < 256 => los pixeles son 1 byte
    for (auto &pixel : imgData) {
        char c;
        infile.get(c);
        pixel = (unsigned char) c;
    }

    infile.close();

    return imgData;
}

imagen vectorAImagen(const vector<double>& v){
    /* Toma un vector de doubles, lo re-escala al rango 0-255
     * y lo castea a `imagen`.
     */
    vector<double> tmp  = reEscalar(v, 0, 255);
    imagen img (tmp.begin(), tmp.end());
    return img;
}

void escribirImagen(const imagen& img, int w, int h, string path){
    ofstream outfile (path, ios::binary);
    outfile << "P5 " << w << " " << h << " 255" << endl;

    for (auto i = 0;  i < w*h; i++){
        outfile << img[i];
    }
    outfile.close();
}
