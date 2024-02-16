#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include "colors.h"

using namespace std;

class celda {
public:
    char letra = ' ';
    bool paso = true;
    int h = 0; // distancia desde punto actual hasta meta
    int g = 0; // distancia desde origen hasta meta
};

//Funciones de main.cpp
pair<int, int> pedirDimensiones();

pair<int, int> pedirCoordenadas(string tipo, int filas, int columnas);

void printMatrix(vector<vector<celda>> matrix);

void trampas(vector<vector<celda>>& matrix);

//Funciones de aEstrella.cpp
double distancia(pair<int, int> a, pair<int, int> b);

bool dentroLimites(pair<int, int> coordenadas, int filas, int columnas);

bool esTransitable(vector<vector<celda>>& matrix, pair<int, int> coordenadas);

vector<pair<int, int>> aEstrella(vector<vector<celda>>& matrix, pair<int, int> inicio, pair<int, int> fin);

void imprimirCamino(vector<pair<int, int>>& camino);
