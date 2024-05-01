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


struct m_y_c
{
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



Vector4d calcular_m(vector<Vector4d> datosClase){
    Vector4d m = { 0, 0, 0, 0 };
    for (auto dato : datosClase) {
        m += dato;
    }
    m = m / 50;
    
    
    return m;
}

Matrix4d calcular_c(vector<Vector4d> datosClase, Vector4d m){
    
    vector<Vector4d> diferencias;
    for (auto x : datosClase){
    Vector4d dif;
        dif = x - m;
        diferencias.push_back(dif);
    }


    Matrix4d covarianza {
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},};
    for(auto d : diferencias){
        covarianza = covarianza + ( d * d.transpose());
    }
    covarianza = covarianza / 50;


    return covarianza;
}

double calcular_distancia(Vector4d x, Vector4d m, Matrix4d c){
    double distancia; 

    Vector4d dif;
    dif = x - m;

    distancia = dif.transpose() * c.completeOrthogonalDecomposition().pseudoInverse() * dif; 

    return distancia;

}



m_y_c entrenar_bayes(vector<Vector4d> irisData) {
    vector<Vector4d> clase1;
    vector<Vector4d> clase2;

    for (int i = 0; i < 50; i++) {
        clase1.push_back(irisData[i]);
    }

    for (int i = 50; i < 100; i++) {
        clase2.push_back(irisData[i]);
    }
    
    Vector4d m1 = calcular_m(clase1);
    Vector4d m2 = calcular_m(clase2);


    cout << endl << endl;
    cout << "m1: " << endl << m1 << endl;
    cout << "m2: " << endl << m2 << endl;
    cout << endl;

    Matrix4d c1 = calcular_c(clase1, m1);
    Matrix4d c2 = calcular_c(clase2, m2);
    cout << "c1: " << endl << c1 << endl;
    cout << "c2: " << endl << c2 << endl;

    return {m1, m2, c1, c2};

}

int bayes_clasificar(m_y_c myc, Vector4d ejemplo){

    if (calcular_distancia(ejemplo, myc.m1, myc.c1) > calcular_distancia(ejemplo, myc.m2, myc.c2))
        return 2;
    else 
        return 1;
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


    m_y_c myc = entrenar_bayes(irisData);
    int ej1 = bayes_clasificar(myc, ejemplo1[0]);
    int ej2 = bayes_clasificar(myc, ejemplo2[0]);
    int ej3 = bayes_clasificar(myc, ejemplo3[0]);
    
    cout << endl;
    cout << "Ej1 es de la clase: " << ej1 << endl;
    cout << "Ej2 es de la clase: " << ej2 << endl;
    cout << "Ej3 es de la clase: " << ej3 << endl;





    //!Para compilar hay que usar g++ -I eigen-3.4.0/ main.cpp -o main.exe
    // Documentación: https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html

    return 0;
}
