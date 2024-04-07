#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
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
};

// Estructura para la conclusión. Arbol n-ario
class node{
public:
    string atributo;
    string valor;
    bool decision;

    node *parent;
    vector<node *> children;

    node(node *parent) : parent(parent)
    {
    }

    void add_child(node *child) { children.push_back(child); }

    // Función para liberar la memoria de forma recursiva
    void destroy_tree(node* root) {
        if (!root) return;
        for (node* child : root->children) {
            destroy_tree(child);
        }
        delete root;
    }

    // Destructor personalizado
    ~node() {
        destroy_tree(this);
    }
};



// Función para leer el fichero AtributosJuego.txt
vector<Atributo> leerAtributos(const string& filename) {
    vector<Atributo> atributos;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo " << filename << endl;
        return atributos;
    }

    string linea;
    Ejemplo aux;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string palabra;
        while (getline(ss, palabra, ',')) {
            Atributo atributo;
            atributo.nombre = palabra;
            atributos.push_back(atributo);
            aux.atributos[palabra] = "";
        }
    }
    file.close();
    return atributos;
}


// Función para leer el fichero Juego.txt
vector<Ejemplo> leerEjemplos(const string& filename, vector<Atributo> atributos) {
    vector<Ejemplo> ejemplos;
    ifstream file(filename);
    string linea;
    int id = 0;
    while (getline(file, linea)) {
        if (linea.empty()) {
            break;
        }
        Ejemplo ejemplo;
        stringstream ss(linea);
        string atributo;
        while (getline(ss, atributo, ',')) {
            ejemplo.atributos[atributos[id].nombre] = atributo;
            id++;
        }
        ejemplo.decision = ejemplo.atributos["Jugar"];
        ejemplo.atributos.erase("Jugar");
        ejemplos.push_back(ejemplo);
        id = 0;
    }
    file.close();
    return ejemplos;
}

// Función para calcular la entropía
double calcularEntropia(vector<Ejemplo>& ejemplos) {
    map<string, int> decisionCounts;
    for (auto& ejemplo : ejemplos) {
        decisionCounts[ejemplo.decision]++;
    }
    double entropia = 0.0;
    for (auto& pair : decisionCounts) {
        double probabilidad = (double)pair.second / ejemplos.size();
        entropia -= probabilidad * log2(probabilidad);
    }
    return entropia;
}

// Función para dividir un conjunto de ejemplos según un atributo dado
map<string, vector<Ejemplo>> dividirEjemplos(vector<Ejemplo>& ejemplos, string atributo) {
    map<string, vector<Ejemplo>> subconjuntos;
    for (auto& ejemplo : ejemplos) {
        string valor_atributo = ejemplo.atributos.at(atributo);
        subconjuntos[valor_atributo].push_back(ejemplo);
    }
    return subconjuntos;
}

// Función para seleccionar el mejor atributo para dividir
string seleccionarMejorAtributo(vector<Ejemplo>& ejemplos, vector<Atributo>& atributos) {
    double mejorGanancia = 1.0;
    string mejorAtributo;
    
    for (auto& atributo : atributos) {
        map<string, vector<Ejemplo>> subconjuntos = dividirEjemplos(ejemplos, atributo.nombre);
        double ganancia = 0.0;
        for (auto& pair : subconjuntos) {
            double peso = (double)pair.second.size() / ejemplos.size();
            ganancia += peso * calcularEntropia(pair.second);
        }
        cout << atributo.nombre << " = " << ganancia << endl;
        if (ganancia < mejorGanancia) {
            mejorGanancia = ganancia;
            mejorAtributo = atributo.nombre;
        }
    }
    return mejorAtributo;
}

// Función principal para el algoritmo ID3
void ID3(vector<Ejemplo>& ejemplos, vector<Atributo>& atributos, int nivel, string& conclusion, node arbolConclusion) {
    cout << "Iteracion " << nivel << endl;
    cout << "--------------------" << endl;

    if (arbolConclusion.parent != &arbolConclusion){
        
    }

    // Caso base si todos tienen la misma decision
    bool mismaDecision = true;
    string decision = ejemplos[0].decision;
    for (auto& ejemplo : ejemplos) {
        if (ejemplo.decision != decision) {
            mismaDecision = false;
            break;
        }
    }
    if (mismaDecision) {
        cout << "Llegada a caso base" << endl << endl;
        for (int i = 0; i < nivel; ++i) {
            conclusion += "\t";
        }
        conclusion += "Entonces Decision = " + decision + "\n";
        arbolConclusion.decision = (decision == "si" ? true : false);
        return;
        
    }

    // Seleccionar el mejor atributo para dividir
    string mejorAtributo = seleccionarMejorAtributo(ejemplos, atributos);

    cout << endl;
    // Recursión para los subárboles
    vector<Atributo> nuevosAtributos = atributos;
    for (auto it = nuevosAtributos.begin(); it != nuevosAtributos.end(); ++it) {
        if (it->nombre == mejorAtributo) {
            nuevosAtributos.erase(it);
            break;
        }
    }
    
    map<string, vector<Ejemplo>> subconjuntos = dividirEjemplos(ejemplos, mejorAtributo);
    for (auto& pair : subconjuntos) {
        for (int i = 0; i < nivel; ++i) {
            conclusion += "\t";
        }
        conclusion += "Si " + mejorAtributo + " = " + pair.first + "\n";

        node* hijo = new node(&arbolConclusion);
        hijo->atributo = mejorAtributo;
        hijo->valor = pair.first;
        arbolConclusion.add_child(hijo);

        ID3(pair.second, nuevosAtributos, nivel + 1, conclusion, hijo);
    }
}

bool comprobarConclusion(const vector<Atributo>& atributos, const vector<Ejemplo>& ejemplos, node conclusion){

}

// Función para imprimir los atributos y ejemplos en forma de tabla
void imprimirTabla(const vector<Atributo>& atributos, const vector<Ejemplo>& ejemplos) {
    // Imprimir encabezado
    for (const auto& atributo : atributos) {
        cout << setw(15) << atributo.nombre;
    }
    cout << setw(15) << "Decision" << endl;

    // Imprimir valores
    for (size_t i = 0; i < ejemplos.size(); ++i) {
        for (const auto& atributo : atributos) {
            cout << setw(15) << ejemplos[i].atributos.at(atributo.nombre);
        }
        cout << setw(15) << ejemplos[i].decision << endl;
    }
    cout << endl;
}

int main() {
    cout << "Construyendo arbol de decision..." << endl;
    // Lectura de los ficheros
    vector<Atributo> atributos = leerAtributos("AtributosJuego.txt");
    vector<Ejemplo> ejemplos = leerEjemplos("Juego.txt", atributos);
    atributos.pop_back();

    // Imprimir la tabla
    imprimirTabla(atributos, ejemplos);

    string conclusion;
    node *arbolConclusion = new node(arbolConclusion);

    // Construcción del árbol de decisión
    ID3(ejemplos, atributos, 0, conclusion, arbolConclusion);

    delete arbolConclusion;

    cout << conclusion << endl;
    
    return 0;
}
