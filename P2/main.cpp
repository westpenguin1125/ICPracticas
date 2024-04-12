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
void ID3(vector<Ejemplo>& ejemplos, vector<Atributo>& atributos, int nivel, string& conclusion, vector<Ejemplo>& v_conclusion, Ejemplo ejemploAux) {
    cout << "Iteracion " << nivel << endl;
    cout << "--------------------" << endl;

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
        ejemploAux.decision = decision;
        v_conclusion.push_back(ejemploAux);
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
        ejemploAux.atributos[mejorAtributo] = pair.first;
        ID3(pair.second, nuevosAtributos, nivel + 1, conclusion, v_conclusion, ejemploAux);
        ejemploAux.atributos.erase(mejorAtributo);
    }
}

bool comprobarConclusion(const  vector<Ejemplo>& ejemplos,const vector<Ejemplo>& conclusiones){
    bool correcto = true;
    int nEjemplos = ejemplos.size();
    cout << conclusiones.size() << endl;
    // para cada ejemplo
    int idEjemplo = 0;
    for (auto &ejemplo : ejemplos){
        idEjemplo++;
        cout <<  endl;
        cout << "_________" << endl;
        cout << "Ejemplo " << idEjemplo << endl; 
        cout << "_________" << endl;
        // se mira cada conclusion
        for(int i = 0; i < conclusiones.size(); i++){
            cout << "   ------ " << i << endl;

            //Si todos los atributos de una conclusión aciertan
            int nAtributosC = conclusiones[i].atributos.size();
            for(auto& atributo : conclusiones[i].atributos){
                if (auto atributo1 = ejemplo.atributos.find(atributo.first); atributo1 != ejemplo.atributos.end()){
                    if (atributo1->second == atributo.second)
                    {
                    nAtributosC--;
                    }
                    cout << atributo.second << " | " << ejemplo.atributos.find(atributo.first)->second<< endl;
                    
                }
            }
            if(nAtributosC <= 0){
                if (ejemplo.decision == conclusiones[i].decision){
                    cout << "---!!!!CORRECTO ("<<idEjemplo<<" )(" << i << ")" << endl;;
                    break;
                }
                else{

                    cout << "¿¿¿¿¿¿¿¿FALSO ("<<idEjemplo<<" )(" << i << ")------------------------------" << endl;;
                    correcto = false;
                }
                
            }
            
        }
        
    }
    return correcto;

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

    vector<Ejemplo> v_conclusion;
    Ejemplo ejemploAux;

    

    // Construcción del árbol de decisión
    ID3(ejemplos, atributos, 0, conclusion, v_conclusion, ejemploAux);
    cout << conclusion << endl;

    for (auto& conclusion : v_conclusion)
    {
        for(auto& atributo : conclusion.atributos){
            cout << atributo.second << ", ";
        }
        cout << conclusion.decision << endl;

    }

    cout << endl << endl;
    bool correcto = comprobarConclusion(ejemplos, v_conclusion);
    
    cout << endl << endl;
    if (correcto)
    {
        cout << "Corecto";
    }
    else{
        cout << "Falso";
    }
    cout << endl;
    

    return 0;
}
