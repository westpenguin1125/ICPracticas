#include "celda.h"

double distancia(pair<int, int> a, pair<int, int> b) {
    return sqrt((pow((b.second+1)-(a.second+1), 2)) + (pow((b.first+1)-(a.first+1), 2)));
}

vector<pair<int, int>> aEstrella(vector<vector<celda>>& matrix, pair<int, int> inicio, pair<int, int> fin) {
    cout << "Ahora veremos el camino mas rapido hacia la meta mediante el uso del algoritmo A*" << endl;
}