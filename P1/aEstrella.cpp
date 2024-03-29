#include "celda.h"

int distancia(pair<int, int> a, pair<int, int> b) {
    return int (sqrt((pow((b.second + 1) - (a.second + 1), 2)) + (pow((b.first + 1) - (a.first + 1), 2))) * 10);
}

bool sePuedePasar(vector<vector<celda>>& matrix, pair<int, int> coordenadas) {
    return matrix[coordenadas.first][coordenadas.second].paso;
}

bool dentroLimites(pair<int, int> coordenadas, int filas, int columnas) {
    return (coordenadas.first >= 0 && coordenadas.first < filas && coordenadas.second >= 0 && coordenadas.second < columnas);
}

queue<pair<int, int>> aEstrella(vector<vector<celda>>& matriz, pair<int, int> inicio, pair<int, int> fin) {
    cout << "Ahora veremos el camino mas rapido hacia la meta mediante el uso del algoritmo A*" << endl;
    int filas = matriz.size();
    int columnas = matriz[0].size();
    queue<pair<int, int>> camino;
    vector<vector<bool>> en_cerrado(filas, vector<bool>(columnas, false)); // celdas visitadas

    priority_queue<pair<int, pair<int, int>>> abierto_priority; // celdas a explorar
    vector<vector<bool>> en_abierto(filas, vector<bool>(columnas, false)); // celdas a explorar bool


    // inicializamos la primera casilla
    matriz[inicio.first][inicio.second].h = distancia(inicio, fin);
    matriz[inicio.first][inicio.second].g = 0;
    matriz[inicio.first][inicio.second].total = matriz[inicio.first][inicio.second].h + matriz[inicio.first][inicio.second].g + matriz[inicio.first][inicio.second].p;
    abierto_priority.push(make_pair(-matriz[inicio.first][inicio.second].total, inicio));

    // inicializamos la última casilla
    matriz[fin.first][fin.second].h = 0;
    matriz[fin.first][fin.second].g = distancia(inicio, fin);
    matriz[fin.first][fin.second].total = matriz[fin.first][fin.second].h + matriz[fin.first][fin.second].g + matriz[fin.first][fin.second].p;
    matriz[fin.first][fin.second].padre = fin;

    while (!abierto_priority.empty()) {
        // celda con menor costo total
        pair<int, int> actual = abierto_priority.top().second;
        abierto_priority.pop();

        en_cerrado[actual.first][actual.second] = true; // marcar celda como visitada
        
        if (actual == fin) { // si la celda actual es la celda final, terminar la búsqueda
            break;
        }

        vector<pair<int, int>> movimientos = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
        for (auto movimiento : movimientos) {
            pair<int, int> nuevaCoordenada = { actual.first + movimiento.first, actual.second + movimiento.second };
            int nuevoG;
            // si la nueva coordenada está dentro de los límites de la matriz y si se puede pasar por ahi
            if (dentroLimites(nuevaCoordenada, filas, columnas)
                && sePuedePasar(matriz, nuevaCoordenada)
                && !en_cerrado[nuevaCoordenada.first][nuevaCoordenada.second]) {

                // calcular el coste de movimiento desde el inicio
                nuevoG = matriz[actual.first][actual.second].g + 10; //ortogonal
                if (abs(movimiento.first) == 1 && abs(movimiento.second) == 1) { //diagonal
                    nuevoG = matriz[actual.first][actual.second].g + 14;
                }
                matriz[nuevaCoordenada.first][nuevaCoordenada.second].p_acum = matriz[nuevaCoordenada.first][nuevaCoordenada.second].p;
                matriz[nuevaCoordenada.first][nuevaCoordenada.second].p_acum += matriz[actual.first][actual.second].p_acum;
                matriz[nuevaCoordenada.first][nuevaCoordenada.second].total = matriz[nuevaCoordenada.first][nuevaCoordenada.second].g + matriz[nuevaCoordenada.first][nuevaCoordenada.second].h + matriz[nuevaCoordenada.first][nuevaCoordenada.second].p_acum;

                //int pTotal =  matriz[nuevaCoordenada.first][nuevaCoordenada.second].p + matriz[actual.first][actual.second].p;
                //matriz[nuevaCoordenada.first][nuevaCoordenada.second].total = matriz[nuevaCoordenada.first][nuevaCoordenada.second].g + matriz[nuevaCoordenada.first][nuevaCoordenada.second].h + pTotal;
                
                // si la celda no ha sido visitada o el nuevo coste de movimiento es menor que el anterior
                if (!en_abierto[nuevaCoordenada.first][nuevaCoordenada.second]
                    || nuevoG < matriz[nuevaCoordenada.first][nuevaCoordenada.second].g) {

                    // actualizar el coste de movimiento
                    matriz[nuevaCoordenada.first][nuevaCoordenada.second].g = nuevoG;
                    matriz[nuevaCoordenada.first][nuevaCoordenada.second].h = distancia(nuevaCoordenada, fin);
                    matriz[nuevaCoordenada.first][nuevaCoordenada.second].total = matriz[nuevaCoordenada.first][nuevaCoordenada.second].g + matriz[nuevaCoordenada.first][nuevaCoordenada.second].h + matriz[nuevaCoordenada.first][nuevaCoordenada.second].p_acum;
                    
                    // marcar la celda actual como padre de la nueva celda
                    matriz[nuevaCoordenada.first][nuevaCoordenada.second].padre = actual;

                    // si la celda no ha sido visitada, añadirla a la lista de celdas a explorar
                    if (!en_abierto[nuevaCoordenada.first][nuevaCoordenada.second]) {
                        en_abierto[nuevaCoordenada.first][nuevaCoordenada.second] = true;
                        abierto_priority.push(make_pair(-matriz[nuevaCoordenada.first][nuevaCoordenada.second].total, nuevaCoordenada));
                    }

                }
            }
        }
    }

    // si no hay camino, terminar la búsqueda
    if (matriz[fin.first][fin.second].padre == fin) {
        cout << "No hay camino posible" << endl;
        return camino;
    }

    // reconstruir el camino desde la celda final hasta la celda inicial
    pair<int, int> actual = fin;
    while (actual != inicio) {
        camino.push(actual);
        actual = matriz[actual.first][actual.second].padre;
    }

    return camino;
}

void imprimirCamino(queue<pair<int, int>>& camino, vector<vector<celda>>& matriz) {
    if (!camino.empty()) {
        cout << "Camino: ";
        while (!camino.empty()) { // imprimimos el camino con una pausa de un segundo por cada movimiento
            matriz[camino.front().first][camino.front().second].camino = true;
            printMatrix(matriz);
            camino.pop();
            
            Sleep(1000); // Sleep 1 segundo para windows
            //sleep(1); // Sleep 1 segundo para linux
        }
        cout << endl;
    }
}