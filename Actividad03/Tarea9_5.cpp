#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <omp.h>
#include <climits>
#include <fstream>
using namespace std;

vector<string> generarMovimientos(const string &estado) {
    vector<string> hijos;
    int pos = estado.find('#');
    int fila = pos / 4, col = pos % 4;

    if (fila > 0) { string nuevo = estado; swap(nuevo[pos], nuevo[pos - 4]); hijos.push_back(nuevo); }
    if (fila < 3) { string nuevo = estado; swap(nuevo[pos], nuevo[pos + 4]); hijos.push_back(nuevo); }
    if (col > 0) { string nuevo = estado; swap(nuevo[pos], nuevo[pos - 1]); hijos.push_back(nuevo); }
    if (col < 3) { string nuevo = estado; swap(nuevo[pos], nuevo[pos + 1]); hijos.push_back(nuevo); }

    return hijos;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);             

    ifstream archivo("puzzles.txt");
    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir puzzles.txt" << endl;
        return 1;
    }

    string inicio;
    string objetivo = "ABCDEFGHIJKLMNO#";

    while (getline(archivo, inicio)) {
        if (inicio.empty()) continue;

        double start_time = omp_get_wtime();

        unordered_map<string, int> distancia;
        vector<string> actualNivel;
        vector<string> siguienteNivel;
        distancia[inicio] = 0;
        actualNivel.push_back(inicio);

        bool encontrado = false;
        int profundidad = 0;

        int numHilos = 4;
        omp_set_num_threads(numHilos);

        vector<int> nodosPorHilo(numHilos, 0);

        while (!actualNivel.empty() && !encontrado) {
            siguienteNivel.clear();

            #pragma omp parallel
            {
                vector<string> localSiguiente;
                int id = omp_get_thread_num();

                #pragma omp for schedule(dynamic)
                for (int i = 0; i < (int)actualNivel.size(); i++) {
                    string actual = actualNivel[i];
                    nodosPorHilo[id]++;

                    vector<string> hijos = generarMovimientos(actual);
                    for (const string &hijo : hijos) {
                        #pragma omp critical
                        {
                            if (!distancia.count(hijo)) {
                                distancia[hijo] = profundidad + 1;
                                if (hijo == objetivo) {
                                    encontrado = true;
                                }
                                localSiguiente.push_back(hijo);
                            }
                        }
                    }
                }

                #pragma omp critical
                {
                    siguienteNivel.insert(siguienteNivel.end(),
                                          localSiguiente.begin(), localSiguiente.end());
                }
            }

            actualNivel = siguienteNivel;
            profundidad++;
        }

        double end_time = omp_get_wtime();
        double tiempo = end_time - start_time;

        
        cout << "===============================" << endl;
        cout << "Estado inicial: " << inicio << endl;
        if (encontrado)
            cout << "Costo (pasos): " << profundidad << endl;
        else
            cout << "Costo (pasos): -1" << endl;

        int totalNodos = 0;
        for (int n : nodosPorHilo) totalNodos += n;

        cout << "Nodos expandidos: " << totalNodos << endl;
        cout << "Tiempo (s): " << tiempo << endl;
        cout << "===============================" << endl;
        cout.flush(); 
    }

    archivo.close();
    return 0;
}
