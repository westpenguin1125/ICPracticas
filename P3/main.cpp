#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;
 
using namespace std;

struct IrisData {
    double x1;
    double x2;
    double x3;
    double x4;
    string nombre_clase;
};

vector<IrisData> readIrisData(const string& filename) {
    vector<IrisData> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        IrisData entry;
        char comma;

        ss >> entry.x1 >> comma
            >> entry.x2 >> comma
            >> entry.x3 >> comma
            >> entry.x4 >> comma
            >> entry.nombre_clase;

        data.push_back(entry);
    }

    file.close();
    return data;
}



IrisData calcular_m(vector<IrisData> datosClase){
    IrisData m = { 0, 0, 0, 0 };
    for (auto dato : datosClase) {
        m.x1 += dato.x1;
        m.x2 += dato.x2;
        m.x3 += dato.x3;
        m.x4 += dato.x4;
    }
    m.x1 = m.x1 / 50;
    m.x2 = m.x2 / 50;
    m.x3 = m.x3 / 50;
    m.x4 = m.x4 / 50;
    

    return m;
}

void calcular_c(vector<IrisData> datosClase, IrisData m){
    vector<IrisData> diferencia;
    for (auto x : datosClase){
    IrisData aux;
        aux.x1 = x.x1 - m.x1;
        aux.x2 = x.x2 - m.x2;
        aux.x3 = x.x3 - m.x3;
        aux.x4 = x.x4 - m.x4;
        diferencia.push_back(aux);
    }
    vector<vector<double>> covarianza;
    for (auto x : diferencia){
        vector<double> aux;

    }
}



void bayes(vector<IrisData> irisData) {
    vector<IrisData> clase1;
    vector<IrisData> clase2;

    for (auto c : irisData) {
        if (c.nombre_clase == "Iris-setosa")
        {
            clase1.push_back(c);
        }
        else
        {
            clase2.push_back(c);
        }
    }
    IrisData m1 = calcular_m(clase1);
    IrisData m2 = calcular_m(clase2);


    cout << "m1: " << m1.x1 << ", " << m1.x2 << ", " << m1.x3 << ", " << m1.x4 << ", " << endl;
    cout << "m2: " << m2.x1 << ", " << m2.x2 << ", " << m2.x3 << ", " << m2.x4 << ", ";
    cout << endl;


}

int main() {
    vector<IrisData> irisData = readIrisData("Iris2Clases.txt");

    cout << "a" << endl;

    // Imprimir los datos leídos
    for (const auto& entry : irisData) {
        cout << "x1: " << entry.x1 << ", "
            << "x2: " << entry.x2 << ", "
            << "x3: " << entry.x3 << ", "
            << "x4: " << entry.x4 << ", "
            << "Clase: " << entry.nombre_clase << endl;
    }

    bayes(irisData);

    cout << endl << "-------------" << endl;
    cout << "Comprobación de que Eigen funciona:" << endl;
    
    MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;

    return 0;
}
