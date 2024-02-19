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
    vector<pair<int, int>> camino;
    vector<vector<bool>> visitado(filas, vector<bool>(columnas, false)); // celdas visitadas
    priority_queue<pair<int, pair<int, int>>> colaPrioridad; // celdas a explorar

    // inicializamos la primera casilla
    matriz[inicio.first][inicio.second].h = distancia(inicio, fin);
    matriz[inicio.first][inicio.second].g = 0;
    matriz[inicio.first][inicio.second].total = matriz[inicio.first][inicio.second].h + matriz[inicio.first][inicio.second].g;
    colaPrioridad.push(make_pair(-matriz[inicio.first][inicio.second].total, inicio));
    
    while (!colaPrioridad.empty()) {
        // celda con menor costo total
        pair<int, int> actual = colaPrioridad.top().second;
        colaPrioridad.pop();

        visitado[actual.first][actual.second] = true; // marcar celda como visitada

        if (actual == fin) { // si la celda actual es la celda final, terminar la búsqueda
            break;
        }

        vector<pair<int, int>> movimientos = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (auto movimiento : movimientos) {
            pair<int, int> nuevaCoordenada = {actual.first + movimiento.first, actual.second + movimiento.second};

            // si la nueva coordenada está dentro de los límites de la matriz y si se puede pasar por ahi
            if (dentroLimites(nuevaCoordenada, filas, columnas) && sePuedePasar(matriz, nuevaCoordenada)) {
                int nuevoG = matriz[actual.first][actual.second].g + 1; // calcular el coste de movimiento desde el inicio

                // si la celda no ha sido visitada o el nuevo coste de movimiento es menor que el anterior
                if (!visitado[nuevaCoordenada.first][nuevaCoordenada.second] || nuevoG < matriz[nuevaCoordenada.first][nuevaCoordenada.second].g) {
                    matriz[nuevaCoordenada.first][nuevaCoordenada.second].g = nuevoG;
                    matriz[nuevaCoordenada.first][nuevaCoordenada.second].h = distancia(nuevaCoordenada, fin);
                    matriz[nuevaCoordenada.first][nuevaCoordenada.second].total = matriz[nuevaCoordenada.first][nuevaCoordenada.second].g + matriz[nuevaCoordenada.first][nuevaCoordenada.second].h;

                    matriz[nuevaCoordenada.first][nuevaCoordenada.second].padre = actual;

                    colaPrioridad.push(make_pair(-matriz[nuevaCoordenada.first][nuevaCoordenada.second].total, nuevaCoordenada));
                }
            }
        }
    }

    // reconstruir el camino desde la celda final hasta la celda inicial
    pair<int, int> actual = fin;
    while (actual != inicio) {
        camino.push_back(actual);
        actual = matriz[actual.first][actual.second].padre;
    }
    camino.push_back(inicio);

    // invertir el camino para que esté en el orden correcto
    reverse(camino.begin(), camino.end());

    return camino;
}

void imprimirCamino(vector<pair<int, int>>& camino, vector<vector<celda>>& matriz) {
    cout << "Camino: ";
    for (auto coordenadas : camino) { // imprimimos el camino con una pausa de un segundo por cada movimiento
        matriz[coordenadas.first][coordenadas.second].letra = '.';
        printMatrix(matriz);
        Sleep(1000);
    }
    cout << endl;
}