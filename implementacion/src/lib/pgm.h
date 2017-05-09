#ifndef PGM_READER_H
#define PGM_READER_H

using namespace std;

imagen levantarImagen(string path);
void escribirImagen(const imagen& img, int w, int h, string path);
imagen vectorAImagen(const vector<double>& v);

#endif // PGM_READER_H
