#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> pedirDimensiones(){
    int filas, columnas;
    
    do {
        cout << "Inserta el numero de filas:" << endl;
        cin >> filas;
    } while (filas < 0);

    do {
        cout << "Inserta el numero de columnas:" << endl;
        cin >> columnas;
    } while (columnas < 0);

    return make_pair(filas, columnas);
}

pair<int, int> pedirCoordenadasIni(int filas, int columnas){
    int x, y;

    cout << "Para el punto inicial:" << endl;
    do {
        cout << "Inserta la coordenada x:" << endl;
        cin >> x;
    } while (x >= filas || x < 0);
    
    do {
        cout << "Inserta la coordenada y:" << endl;
        cin >> y;
    } while (y >= columnas || y < 0);

    return make_pair(x, y);
}

pair<int, int> pedirCoordenadasFin(int filas, int columnas){
    int x, y;

    cout << "Para el punto inicial:" << endl;
    do {
        cout << "Inserta la coordenada x:" << endl;
        cin >> x;
    } while (x >= filas || x < 0);
    
    do {
        cout << "Inserta la coordenada y:" << endl;
        cin >> y;
    } while (y >= columnas || y < 0);

    return make_pair(x, y);
}

void printMatrix(vector<vector<char>> matrix){
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void rellenarMatrix(vector<vector<char>> &matrix, pair<int, int> coordenadasIni, pair<int, int> coordenadasFin){
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            if (i == matrix.size() - 1 - coordenadasIni.first && j == coordenadasIni.second) {
                matrix[i][j] = 'o';
            } else if (i == matrix.size() - 1 - coordenadasFin.first && j == coordenadasFin.second) {
                matrix[i][j] = 'f';
            } else {
                matrix[i][j] = '-';
            }
        }
    }
}



int main (){

    pair<int, int> dimensiones = pedirDimensiones();
    int filas = dimensiones.first;
    int columnas = dimensiones.second;

    pair<int, int> coordenadasIni = pedirCoordenadasIni(filas, columnas);
    pair<int, int> coordenadasFin = pedirCoordenadasFin(filas, columnas);

    vector<vector<char>> matriz(filas, vector<char>(columnas, 0));
    rellenarMatrix(matriz, coordenadasIni, coordenadasFin);
    printMatrix(matriz);

    return 0;
}