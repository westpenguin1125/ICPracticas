#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//Librería de matrices
//!Para compilar hay que usar g++ -I eigen-3.4.0/ main.cpp -o main.exe
#include <Eigen/Dense>
 
using Eigen::Matrix4d;
using Eigen::Vector4d;

using namespace std;

double tolerancia = 0.0000000001;
int maximasIteraciones = 10;
double razonAprendizaje = 0.1; //(gamma)

Vector4d v1 (4.6, 3.0, 4.0, 0.0);
Vector4d v2 (6.8, 3.4, 4.6, 0.7);

struct m_y_c {
    Vector4d m1;
    Vector4d m2;
    Matrix4d c1;
    Matrix4d c2;
};


vector<Vector4d> readIrisData(const string& filename) {
    vector<Vector4d> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Vector4d entry;
        char comma;

        ss >> entry(0) >> comma
            >> entry(1) >> comma
            >> entry(2) >> comma
            >> entry(3) >> comma;

        data.push_back(entry);
    }

    file.close();
    return data;
}

void calcularD() {

}

void lloyd(vector<Vector4d> ejemplo1, vector<Vector4d> ejemplo2, vector<Vector4d> ejemplo3) {
    
}



int main() {
    vector<Vector4d> irisData = readIrisData("Iris2Clases.txt");

    // Imprimir los datos leídos
    cout << "Datos Leidos:" << endl << "_____________" << endl;
    for (int i = 0; i < irisData.size(); i++) {
        cout << i << ": " << irisData[i].transpose() << endl;
        if (i == 49) {cout << endl;}
    }
    cout << "____________________" << endl;

    vector<Vector4d> ejemplo1 = readIrisData("TestIris01.txt");
    vector<Vector4d> ejemplo2 = readIrisData("TestIris02.txt");
    vector<Vector4d> ejemplo3 = readIrisData("TestIris03.txt");


    //!Para compilar hay que usar g++ -I eigen-3.4.0/ main.cpp -o main.exe
    // Documentación: https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html

    return 0;
}
