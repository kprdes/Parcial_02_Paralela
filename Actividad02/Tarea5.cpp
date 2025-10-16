#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <chrono> 
using namespace std;

string objetivo = "ABCDEFGHIJKLMNO#";

int heuristica(const string &estado) {
    int h = 0;
    for (int i = 0; i < 16; i++) {
        if (estado[i] != '#' && estado[i] != objetivo[i]) {
            h++;
        }
    }
    return h;
}

vector<string> generarMovimientos(const string &estado) {
    vector<string> hijos;
    int pos = estado.find('#');
    int fila = pos / 4, col = pos % 4;

    if (fila > 0) {
        string nuevo = estado;
        swap(nuevo[pos], nuevo[pos - 4]);
        hijos.push_back(nuevo);
    }
    if (fila < 3) {
        string nuevo = estado;
        swap(nuevo[pos], nuevo[pos + 4]);
        hijos.push_back(nuevo);
    }
    if (col > 0) {
        string nuevo = estado;
        swap(nuevo[pos], nuevo[pos - 1]);
        hijos.push_back(nuevo);
    }
    if (col < 3) {
        string nuevo = estado;
        swap(nuevo[pos], nuevo[pos + 1]);
        hijos.push_back(nuevo);
    }

    return hijos;
}

struct Nodo {
    string estado;
    int g;
    int f;
    bool operator>(const Nodo &otro) const {
        return f > otro.f;
    }
};

int main() {
    ifstream archivo("puzzles.txt");
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo puzzles.txt" << endl;
        return 1;
    }

    string inicio;

    while (getline(archivo, inicio)) {
        if (inicio.empty()) continue;

        cout << "===============================" << endl;
        cout << "Estado inicial: " << inicio << endl;

        if (inicio == objetivo) {
            cout << "Costo (pasos): 0" << endl;
            cout << "Nodos expandidos: 0" << endl;
            cout << "Tiempo (s): 0" << endl;
            continue;
        }

        auto inicioTiempo = chrono::high_resolution_clock::now();

        priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;
        unordered_map<string, int> costo;

        pq.push({inicio, 0, heuristica(inicio)});
        costo[inicio] = 0;

        int nodosExpandidos = 0;
        bool solucionEncontrada = false;

        while (!pq.empty()) {
            Nodo actual = pq.top();
            pq.pop();
            nodosExpandidos++;

            if (actual.estado == objetivo) {
                auto finTiempo = chrono::high_resolution_clock::now();
                chrono::duration<double> duracion = finTiempo - inicioTiempo;

                cout << "Costo (pasos): " << actual.g << endl;
                cout << "Nodos expandidos: " << nodosExpandidos << endl;
                cout << "Tiempo (s): " << duracion.count() << endl;
                solucionEncontrada = true;
                break;
            }

            vector<string> hijos = generarMovimientos(actual.estado);

            for (auto &hijo : hijos) {
                int nuevoG = actual.g + 1;
                if (!costo.count(hijo) || nuevoG < costo[hijo]) {
                    costo[hijo] = nuevoG;
                    int nuevoF = nuevoG + heuristica(hijo);
                    pq.push({hijo, nuevoG, nuevoF});
                }
            }
        }

        if (!solucionEncontrada) {
            auto finTiempo = chrono::high_resolution_clock::now();
            chrono::duration<double> duracion = finTiempo - inicioTiempo;

            cout << "No se encontró solución" << endl;
            cout << "Nodos expandidos: " << nodosExpandidos << endl;
            cout << "Tiempo (s): " << duracion.count() << endl;
        }
    }

    archivo.close();
    return 0;
}
