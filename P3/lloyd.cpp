#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib> //-> para rand()

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

//inicialización aleatoria de los centros
vector<Vector4d> ini_c_rand(int numCentros){
    vector<Vector4d> centros;
    Vector4d centro;

    srand(time(nullptr));
    for (int i = 0; i < numCentros; i++)
    {
        
        centro(0) = double(rand() % 70) / 10;
        centro(1) = double(rand() % 70) / 10;
        centro(2) = double(rand() % 70) / 10;
        centro(3) = double(rand() % 70) / 10;
        centros.push_back(centro);
    }
    return centros;
}

//inicialización definida de los centros (según el apéndice del enunciado)
vector<Vector4d> ini_c_forced(){
    vector<Vector4d> centros;

    Vector4d c1(4.6, 3.0, 4.0, 0.0);
    centros.push_back(c1);
    Vector4d c2(6.8, 3.4, 4.6, 0.7);
    centros.push_back(c2);

    return centros;
}

//Calcula la distancia euclidiana entre dos vectores
double calcularD(Vector4d x, Vector4d c) {
    return sqrt( pow(x(0) - c(0), 2) 
                + pow(x(1) - c(1), 2) 
                + pow(x(2) - c(2), 2) 
                + pow(x(3) - c(3), 2)
                );
}

//Calcula el centro más cercano a un vector x 
int calcularC_mas_proximo(Vector4d x, vector<Vector4d> centros){
    int i_cMasProximo = 0;
    double distancia_cMasProximo = 10000;
    for(int i = 0; i < centros.size(); i++){
        double distancia = calcularD(x, centros.at(i));
        if (distancia < distancia_cMasProximo){
            i_cMasProximo = i;
            distancia_cMasProximo = distancia;
        }
    }
    
    return i_cMasProximo;
}

//Actualiza el centro que se le pase para que se acerque al vector x
void actualizarC(Vector4d& c, Vector4d x){
    c = c + ( razonAprendizaje * (x-c));
}


void entrenar_lloyd(vector<Vector4d> irisData) {

    vector<Vector4d> centros = ini_c_forced();

    cout <<"|c1= " << centros.at(0).transpose()  << " |c2= " << centros.at(1).transpose() << "\n\n"; 
    int i_cMasProximo;
    for (int j = 0; j < maximasIteraciones; j++)
    {
        for (int i = 0; i < irisData.size(); i++){
        i_cMasProximo = calcularC_mas_proximo(irisData.at(i), centros);
        cout << "Más proximo = " << i_cMasProximo+1 << " |";
        actualizarC(centros.at(i_cMasProximo), irisData.at(i));
        cout << "new_c" << i_cMasProximo+1 <<"= " << centros.at(i_cMasProximo).transpose() << endl;
        }
    }
    cout << "__________________________" << endl << endl;
    cout << "centros finales:" << endl;
    for (int i = 0; i < centros.size(); i++)
    {
        cout << "c" << i+1 << "= " << centros.at(i).transpose() << endl;
    }
    

}


void clasificar_lloyd(vector<Vector4d> ejemplo1, vector<Vector4d> ejemplo2, vector<Vector4d> ejemplo3) {
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

    entrenar_lloyd(irisData);
    clasificar_lloyd(ejemplo1, ejemplo2, ejemplo3);

    //!Para compilar hay que usar g++ -I eigen-3.4.0/ main.cpp -o main.exe
    // Documentación: https://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html

    return 0;
}
