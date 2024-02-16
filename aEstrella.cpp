#include "celda.h"

double distancia(pair<int, int> a, pair<int, int> b) {
    return sqrt((pow(b.first-a.first, 2)) + (pow(b.second-a.second, 2)));
}

vector<pair<int, int>> aEstrella(vector<vector<celda>>& matrix, pair<int, int> inicio, pair<int, int> fin) {
    cout << "Ahora veremos el camino mas rapido hacia la meta mediante el uso del algoritmo A*" << endl;
}