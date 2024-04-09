#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct IrisData {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    string class_label;
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

        ss >> entry.sepal_length >> comma
            >> entry.sepal_width >> comma
            >> entry.petal_length >> comma
            >> entry.petal_width >> comma
            >> entry.class_label;

        data.push_back(entry);
    }

    file.close();
    return data;
}

int main() {
    vector<IrisData> irisData = readIrisData("Iris2Clases.txt");

    // Imprimir los datos leídos
    for (const auto& entry : irisData) {
        cout << "Sepal Length: " << entry.sepal_length << ", "
            << "Sepal Width: " << entry.sepal_width << ", "
            << "Petal Length: " << entry.petal_length << ", "
            << "Petal Width: " << entry.petal_width << ", "
            << "Class: " << entry.class_label << endl;
    }

    return 0;
}
