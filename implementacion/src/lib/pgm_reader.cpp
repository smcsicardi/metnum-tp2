#include <iostream>
#include <fstream>
#include <limits>

#include "tipos.h"
#include "utilities.h"
#include "pgm_reader.h"

using namespace std;

imagen levantarImagen(string path){
    /* Parseando PGM de acuerdo a
     * http://netpbm.sourceforge.net/doc/pgm.html
     */
    ifstream infile (path, ios::binary);

    if (!infile.is_open()) {
        cout << "path = " << path << endl;
        fail("Unable to open file.");
    }

    // los 4 valores que tiene el header: version w h maxVal
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
    // int maxVal = stoi(vals[3]);

    if(version.compare("P5") != 0){
        fail("No es P5");
    }

    // cout << "Version: " << version << endl;
    // cout << "Max val: " << maxVal << endl;
    // cout << width << " columns and " << height << " rows" << endl;

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
