#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

using namespace std;

// Estructura para un ejemplo
struct Ejemplo {
    unordered_map<string, string> atributos;
    string decision;
};

// Estructura para un atributo
struct Atributo {
    string nombre;
    vector<string> valores;
};

// Función para leer el fichero de atributos
vector<Atributo> leerAtributos(const string& filename) {
    vector<Atributo> atributos;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Atributo atributo;
        atributo.nombre = line;
        atributos.push_back(atributo);
    }
    file.close();
    return atributos;
}

// Función para leer el fichero de juegos
vector<Ejemplo> leerEjemplos(const string& filename, const vector<Atributo>& atributos) {
    vector<Ejemplo> ejemplos;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Ejemplo ejemplo;
        stringstream ss(line);
        string atributo;
        int id = 0;
        while (getline(ss, atributo, ',')) {
            ejemplo.atributos[atributos[id].nombre] = atributo;
            id++;
        }
        ejemplo.decision = ejemplo.atributos[atributos.back().nombre];
        ejemplo.atributos.erase(atributos.back().nombre);
        ejemplos.push_back(ejemplo);
    }
    file.close();
    return ejemplos;
}

// Función para calcular la entropía
double calcularEntropia(const vector<Ejemplo>& ejemplos) {
    unordered_map<string, int> decisiones;
    for (const auto& ejemplo : ejemplos) {
        decisiones[ejemplo.decision]++;
    }
    double entropia = 0.0;
    for (const auto& par : decisiones) {
        double probabilidad = static_cast<double>(par.second) / ejemplos.size();
        entropia -= probabilidad * log2(probabilidad);
    }
    return entropia;
}

// Función para calcular la ganancia de información
double calcularGanancia(const vector<Ejemplo>& ejemplos, const Atributo& atributo) {
    unordered_map<string, vector<Ejemplo>> subconjuntos;
    for (const auto& ejemplo : ejemplos) {
        subconjuntos[ejemplo.atributos.at(atributo.nombre)].push_back(ejemplo);
    }
    double ganancia = calcularEntropia(ejemplos);
    for (const auto& par : subconjuntos) {
        double probabilidad = static_cast<double>(par.second.size()) / ejemplos.size();
        ganancia -= probabilidad * calcularEntropia(par.second);
    }
    return ganancia;
}

// Función para seleccionar el mejor atributo
Atributo seleccionarMejorAtributo(const vector<Ejemplo>& ejemplos, const vector<Atributo>& atributos) {
    double mejorGanancia = -1.0;
    Atributo mejorAtributo;
    for (const auto& atributo : atributos) {
        double ganancia = calcularGanancia(ejemplos, atributo);
        if (ganancia > mejorGanancia) {
            mejorGanancia = ganancia;
            mejorAtributo = atributo;
        }
    }
    return mejorAtributo;
}

// Función para construir el árbol de decisión
void construirArbol(const vector<Ejemplo>& ejemplos, const vector<Atributo>& atributos) {
    // Implementa aquí tu algoritmo para construir el árbol de decisión
}

int main() {
    // Lectura de los ficheros
    vector<Atributo> atributos = leerAtributos("AtributosJuego.txt");
    vector<Ejemplo> ejemplos = leerEjemplos("Juego.txt", atributos);

    // Construcción del árbol de decisión
    construirArbol(ejemplos, atributos);

    return 0;
}



