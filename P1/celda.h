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
    char letra = ' '; // La letra que se muestra en la vista
    bool camino = false; // Si es camino o no, para la vista

    bool paso = true; // Si es trampa o no
    double h = 0; // distancia desde punto actual hasta meta
    double g = 0; // distancia desde origen hasta el punto actual
    double p = 0; // indice de peligrosidad asignado (el que se muestra)
    double p_acum = 0; // indice de peligrosidad acumulado (calculo interno)
    double total = 0; // suma de h, g y p_acum
    pair<int, int> padre; // Las coordenadas x,y de la casilla padre
};

//Funciones de main.cpp
pair<int, int> pedirDimensiones();

pair<int, int> pedirCoordenadas(string tipo, int filas, int columnas);

void printMatrix(vector<vector<celda>> matrix);

void trampas(vector<vector<celda>>& matrix);

bool comprobarLibre(vector<vector<celda>> matrix, pair<int, int> coordenadas);

double pedirIndice();

void peligros(vector<vector<celda>>& matrix);

queue<pair<int, int>> waypoints(vector<vector<celda>>& matrix);

//Funciones de aEstrella.cpp
int distancia(pair<int, int> a, pair<int, int> b);

bool dentroLimites(pair<int, int> coordenadas, int filas, int columnas);

bool sePuedePasar(vector<vector<celda>>& matrix, pair<int, int> coordenadas);

queue<pair<int, int>> aEstrella(vector<vector<celda>>& matrix, pair<int, int> inicio, pair<int, int> fin);

void imprimirCamino(queue<pair<int, int>>& camino, vector<vector<celda>>& matriz);
