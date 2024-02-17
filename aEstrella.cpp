#include "celda.h"

double distancia(pair<int, int> a, pair<int, int> b) {
    return sqrt((pow((b.second+1)-(a.second+1), 2)) + (pow((b.first+1)-(a.first+1), 2)));
}

bool sePuedePasar(vector<vector<celda>>& matrix, pair<int, int> coordenadas) {
    return matrix[coordenadas.first][coordenadas.second].paso;
}

bool dentroLimites(pair<int, int> coordenadas, int filas, int columnas) {
    return (coordenadas.first >= 0 && coordenadas.first < filas && coordenadas.second >= 0 && coordenadas.second < columnas);
}

vector<pair<int, int>> aEstrella(vector<vector<celda>>& matriz, pair<int, int> inicio, pair<int, int> fin) {
    cout << "Ahora veremos el camino mas rapido hacia la meta mediante el uso del algoritmo A*" << endl;
    int filas = matriz.size();
    int columnas = matriz[0].size();

    // inicializamos la primera casilla
    matriz[inicio.first][inicio.second].h = distancia(inicio, fin);
    matriz[inicio.first][inicio.second].g = 0;
    matriz[inicio.first][inicio.second].total = matriz[inicio.first][inicio.second].h + matriz[inicio.first][inicio.second].g;
}

void imprimirCamino(vector<pair<int, int>>& camino, vector<vector<celda>>& matriz) {
    cout << "Camino: ";
    for (auto coordenadas : camino) {
        matriz[coordenadas.first][coordenadas.second].letra = '.';
        printMatrix(matriz);
    }
    cout << endl;
}