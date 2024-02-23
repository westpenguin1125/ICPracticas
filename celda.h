#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> //para reverse
#include <windows.h> // para sleep
//#include <unistd.h> //sleep en linux
#include "colors.h"

using namespace std;

class celda {
public:
    char letra = ' ';
    bool paso = true;
    double h = 0; // distancia desde punto actual hasta meta
    double g = 0; // distancia desde origen hasta el punto actual
    double total = 0; // suma de h y g
    pair<int,int> padre;
};

//Funciones de main.cpp
pair<int, int> pedirDimensiones();

pair<int, int> pedirCoordenadas(string tipo, int filas, int columnas);

pair<int, int> cargarDimensiones(const std::string& filePath);

pair<int, int> cargarCoordenadas(const std::string& filePath, const std::string& tipo);

void printMatrix(vector<vector<celda>> matrix);

void trampas(vector<vector<celda>>& matrix);

//Funciones de aEstrella.cpp
double distancia(pair<int, int> a, pair<int, int> b);

bool dentroLimites(pair<int, int> coordenadas, int filas, int columnas);

bool sePuedePasar(vector<vector<celda>>& matrix, pair<int, int> coordenadas);

vector<pair<int, int>> aEstrella(vector<vector<celda>>& matrix, pair<int, int> inicio, pair<int, int> fin, vector<pair<int, int>> wp);

void imprimirCamino(vector<pair<int, int>>& camino, vector<vector<celda>>& matriz);
