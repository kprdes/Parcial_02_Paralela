#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>   
#include <chrono>    
using namespace std;

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

int main() {
    
    ifstream archivo("puzzles.txt");
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo puzzles.txt" << endl;
        return 1;
    }

    string inicio;
    string objetivo = "ABCDEFGHIJKLMNO#";

    
    while (getline(archivo, inicio)) {
        if (inicio.empty()) continue; 

        cout << "===============================" << endl;
        cout << "Estado inicial: " << inicio << endl;

        
        auto t_start = chrono::high_resolution_clock::now();

        if (inicio == objetivo) {
            auto t_end = chrono::high_resolution_clock::now();
            double tiempo = chrono::duration_cast<chrono::duration<double>>(t_end - t_start).count();

            cout << "Costo (pasos): 0" << endl;
            cout << "Nodos expandidos: 0" << endl;
            cout << "Tiempo (s): " << tiempo << endl;
            continue;
        }

        queue<string> q;
        unordered_map<string, int> distancia;

        q.push(inicio);
        distancia[inicio] = 0;

        int nodosExpandidos = 0;
        bool solucionEncontrada = false;

        while (!q.empty()) {
            string actual = q.front();
            q.pop();
            nodosExpandidos++;

            int d = distancia[actual];
            vector<string> hijos = generarMovimientos(actual);

            for (const string &hijo : hijos) {
                if (!distancia.count(hijo)) {
                    distancia[hijo] = d + 1;
                    if (hijo == objetivo) {
                        auto t_end = chrono::high_resolution_clock::now();
                        double tiempo = chrono::duration_cast<chrono::duration<double>>(t_end - t_start).count();

                        cout << "Costo (pasos): " << d + 1 << endl;
                        cout << "Nodos expandidos: " << nodosExpandidos << endl;
                        cout << "Tiempo (s): " << tiempo << endl;

                        solucionEncontrada = true;
                        break;
                    }
                    q.push(hijo);
                }
            }
            if (solucionEncontrada) break;
        }

        if (!solucionEncontrada) {
            auto t_end = chrono::high_resolution_clock::now();
            double tiempo = chrono::duration_cast<chrono::duration<double>>(t_end - t_start).count();

            cout << "No se encontró solución" << endl;
            cout << "Nodos expandidos: " << nodosExpandidos << endl;
            cout << "Tiempo (s): " << tiempo << endl;
        }
    }

    archivo.close();
    return 0;
}
