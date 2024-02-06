#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> pedirDimensiones(){
    int columnas;
    int filas;

    cout << "inserta el número de columnas:" << endl;
    cin >> columnas;
    cout << "inserta el número de filas:" << endl;
    cin >> filas;

    return make_pair(columnas, filas);
}

pair<int, int> pedirCoordenadasIni(){
    int x;
    int y;
    cout << "Para el punto inicial" << endl;
    cout << "inserta la coordenada x:" << endl;
    cin >> x;
    cout << "inserta la coordenada y:" << endl;
    cin >> y;

    return make_pair(x, y);
}

pair<int, int> pedirCoordenadasFin(){
    int x;
    int y;
    cout << "Para el punto final" << endl;
    cout << "inserta la coordenada x:" << endl;
    cin >> x;
    cout << "inserta la coordenada y:" << endl;
    cin >> y;

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
            if (i == coordenadasIni.second && j == coordenadasIni.first){
                matrix[i][j] = 'o';
            } else if (i == coordenadasFin.second && j == coordenadasFin.first){
                matrix[i][j] = 'f';
            } else {
                matrix[i][j] = '-';
            }
        }
    }
}



int main (){

    pair<int, int> dimensiones = pedirDimensiones();
    int columnas = dimensiones.first;
    int filas = dimensiones.second;

    pair<int, int> coordenadasIni = pedirCoordenadasIni();

    pair<int, int> coordenadasFin = pedirCoordenadasFin();



    vector<vector<char>> matriz(filas, vector<char>(columnas, 0));
    rellenarMatrix(matriz, coordenadasIni, coordenadasFin);
    printMatrix(matriz);


    return 0;
}