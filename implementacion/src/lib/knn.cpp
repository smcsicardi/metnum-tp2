#include <string>
#include "parser.h"
#include "tipos.h"

using namespace std;

int kNN(const vector<Punto>& X2, const Punto& y, int k, int clases){
    int n = y.coordenadas.size();
    // distancias = [ (persona, distancia) ]
    vector<pair<int, double>> distancias (X2.size());

    // distancias_i = || y - X2_i ||
    for(auto i = 0; i < distancias.size(); i++){
        double dist = 0;
        for (auto j = 0; j < n; j++){
            dist += pow(X2[i].coordenadas[j] - y.coordenadas[j], 2);
        }
        distancias[i].first = X2[i].persona;
        distancias[i].second = sqrt(dist);
    }

    // ordeno sobre second
    std::sort(distancias.begin(), distancias.end(),
        [](pair<int, double> a, pair<int, double> b) {
            return b.second > a.second;
        });

    // votos_i = votos persona i+1
    vector<int> votos (clases);
    for (auto i = 0; i < k; i++){
        votos[distancias[i].first - 1] += 1;
    }

    vector<int>::iterator res = max_element(votos.begin(), votos.end());

    return distance(votos.begin(), res) + 1;
}
