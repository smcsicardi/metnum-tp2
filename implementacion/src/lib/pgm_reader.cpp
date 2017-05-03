#include <iostream>
#include <fstream>

#include "tipos.h"
#include "utilities.h"
#include "pgm_reader.h"

using namespace std;

matriz levantarMatriz(string path){
    /* Parsing PGM according to
     * http://netpbm.sourceforge.net/doc/pgm.html
     */
    ifstream infile (path, std::ios::binary);

    if (!infile.is_open()) {
        fail("Unable to open file.");
    }

    // los 4 valores que requerimos: version w h maxVal
    vector<string> vals (4);
    int count = 0;
    while (count < 4) {
        // leemos en un buffer
        string buff;
        infile >> buff;
        if (buff.compare(0, 1, "#") == 0) {
            // si encontré un #, ignoro hasta newline
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } else {
            // si no, va en vals
            vals[count] = buff;
            count += 1;
        }
    }
    // finalmente ignoro el newline
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    string version = vals[0];
    int width = std::stoi(vals[1]);
    int height = std::stoi(vals[2]);
    int maxVal = std::stoi(vals[3]);

    cout << "Version: " << version << endl;
    cout << "Max val: " << maxVal << endl;
    cout << width << " columns and " << height << " rows" << endl;

    matriz data (height, vector<int> (width));

    // asumo maxVal < 256 => los pixeles son 1 byte
    for (auto &row : data) {
        for (auto &pixel : row) {
            char c;
            infile.get(c);
            pixel = (unsigned char) c;
        }
    }

    infile.close();

    return data;
}
