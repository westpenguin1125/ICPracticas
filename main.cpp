#include "celda.h"

pair<int, int> pedirDimensiones() {
    int filas, columnas;

    do {
        cout << "Inserta el numero de filas (mayor que 0):" << endl;
        cin >> filas;
    } while (filas <= 0);

    do {
        cout << "Inserta el numero de columnas (mayor que 0):" << endl;
        cin >> columnas;
    } while (columnas <= 0);

    return make_pair(filas, columnas);
}

pair<int, int> pedirCoordenadas(string tipo, int filas, int columnas) {
    int x, y;

    cout << "Para " << tipo << ":" << endl;
    do {
        cout << "Inserta la coordenada x (entre 1 y " << columnas << "):" << endl;
        cin >> x;
    } while (x < 1 || x > columnas);

    do {
        cout << "Inserta la coordenada y (entre 1 y " << filas << "):" << endl;
        cin >> y;
    } while (y < 1 || y > filas);

    cout << endl;
    return make_pair(y-1, x-1);
}

void printMatrix(vector<vector<celda>> matrix) {
    cout << endl;
    // Imprimir la esquina superior izquierda
    cout << "  +";

    // Imprimir la línea superior de la matriz con esquinas
    for (int j = 0; j < matrix[0].size(); j++) {
        cout << "---+";
    }
    cout << endl;

    for (int i = matrix.size() - 1; i >= 0; i--) { // Cambiar el orden de las filas
        // Contenido
        cout << i + 1 << " |"; // Imprimir el índice de la fila
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << " ";
            if (matrix[i][j].letra == 'I') {
                cout << YELLOW << matrix[i][j].letra << RESET;
            }
            else if (matrix[i][j].letra == 'F') {
                cout << CYAN << matrix[i][j].letra << RESET;
            }
            else if (matrix[i][j].letra == 'X') {
                cout << RED << matrix[i][j].letra << RESET;
            }
            else if (matrix[i][j].letra == '.') {
                cout << GREEN << matrix[i][j].letra << RESET;
            }
            else {
                cout << matrix[i][j].letra;
            }
            cout << " |";
        }
        cout << endl;

        // Imprimir la línea inferior de cada fila con esquinas
        cout << "  +";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << "---+";
        }
        cout << endl;
    }

    // Imprimir los índices de las columnas
    cout << "    ";
    for (int i = 0; i < matrix[0].size(); i++) {
        cout << i + 1 << "   ";
    }
    cout << endl << endl;
}


void trampas(vector<vector<celda>>& matrix) {
    cout << "Ahora te pedire que digas los lugares en los que habra trampas y por los que no podras cruzar: " << endl;
    string res;
    do {
        cout << "Quieres agregar alguna trampa? (s/n): ";
        cin >> res;
        if (res == "s") {
            pair<int, int> coordenadas = pedirCoordenadas("la trampa", matrix.size(), matrix[0].size());
            cout << "Trampa agregada en la posicion (" << coordenadas.first << ", " << coordenadas.second << ")" << endl;
            matrix[coordenadas.first][coordenadas.second].letra = 'X'; // Agregar trampa a la matriz con coordenadas invertidas
            matrix[coordenadas.first][coordenadas.second].paso = false;
            printMatrix(matrix); // Imprimir la matriz después de agregar una trampa
        }
        else if (res != "n") {
            cout << "Respuesta invalida. Por favor, introduce 's' o 'n'." << endl;
            res = "s";
        }

    } while (res == "s");
}

int main() {
    pair<int, int> dimensiones = pedirDimensiones();
    int filas = dimensiones.first;
    int columnas = dimensiones.second;

    vector<vector<celda>> matriz(filas, vector<celda>(columnas));
    printMatrix(matriz);

    pair<int, int> coordenadasIni = pedirCoordenadas("el punto inicial", filas, columnas);
    pair<int, int> coordenadasFin = pedirCoordenadas("el punto final", filas, columnas);
    matriz[coordenadasIni.first][coordenadasIni.second].letra = 'I';
    matriz[coordenadasFin.first][coordenadasFin.second].letra = 'F';

    printMatrix(matriz);

    trampas(matriz);

    vector<pair<int, int>> camino = aEstrella(matriz, coordenadasIni, coordenadasFin);

    imprimirCamino(camino, matriz);

    return 0;
}