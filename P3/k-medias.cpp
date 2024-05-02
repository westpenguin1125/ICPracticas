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

double tolerancia = 0.01;
double pesoExponencial = 2;

Vector4d v1 (4.6, 3.0, 4.0, 0.0);
Vector4d v2 (6.8, 3.4, 4.6, 0.7);


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

 vector<double> ini_probs(int irisDataSize){
    vector<double> probs;
    double prob = 0.5;
    for (int i = 0; i < irisDataSize; i++)
    {
        probs[i] = 0.5;
    }
    return probs;
 }

//Calcula la distancia euclidiana entre dos vectores
double calcularD(Vector4d x, Vector4d c) {
    return sqrt( pow(x(0) - c(0), 2) 
                + pow(x(1) - c(1), 2) 
                + pow(x(2) - c(2), 2) 
                + pow(x(3) - c(3), 2)
                );
}

//Calcula la probabilidad de que x pertenezca al grupo del centro v.
double calcularP(Vector4d x, Vector4d v) {
    double exponente = 1/(pesoExponencial-1);
    double numerador = pow(1/(calcularD(x, v)), exponente);

    double denominador = 0;
    denominador += pow(1/(calcularD(x, v1)), exponente);
    denominador += pow(1/(calcularD(x, v2)), exponente);

    return numerador/denominador;
}

Vector4d calcularV(vector<Vector4d> irisData, vector<double> probs) {
    Vector4d numerador(0, 0, 0, 0);
    double denominador = 0;
    
    for (int i = 0; i < irisData.size(); i++) {
        numerador += pow(probs.at(i), pesoExponencial) * irisData.at(i);
        denominador += pow(probs.at(i), pesoExponencial);
    }


    return numerador/denominador;

}

void entrenar_kMedias(vector<Vector4d> irisData){
    vector<double> probsv1 = ini_probs(irisData.size());
    vector<double> probsv2 = ini_probs(irisData.size());
    
    Vector4d v1 = calcularV(irisData, probsv1);
    
    for (int i = 0; i < irisData.size(); i++)
    {
        double p = calcularP(irisData.at(i), v1);
        probsv1.push_back(p);

        p = calcularP(irisData.at(i), v2);
        probsv2.push_back(p);   
    }
    cout << "|v1= " << v1.transpose() << endl;
    


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

    entrenar_kMedias(irisData);


    //!Para compilar hay que usar g++ -I eigen-3.4.0/ main.cpp -o main.exe
    // Documentación: https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html

    return 0;
}
