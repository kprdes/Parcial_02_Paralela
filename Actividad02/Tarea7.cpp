#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>
#include <cmath>
using namespace std;


int N; 
string objetivo;


int heuristica(const string &estado) {
    int h = 0;
    for (int i = 0; i < N * N; i++) {
        char c = estado[i];
        if (c == '#') continue;

        int filaActual = i / N;
        int colActual = i % N;

        int posObjetivo = objetivo.find(c);
        int filaObj = posObjetivo / N;
        int colObj = posObjetivo % N;

        h += abs(filaActual - filaObj) + abs(colActual - colObj);
    }
    return h;
}


vector<string> generarMovimientos(const string &estado) {
    vector<string> hijos;
    int pos = estado.find('#');
    int fila = pos / N, col = pos % N;

    if (fila > 0) {
        string nuevo = estado;
        swap(nuevo[pos], nuevo[pos - N]);
        hijos.push_back(nuevo);
    }
    if (fila < N - 1) {
        string nuevo = estado;
        swap(nuevo[pos], nuevo[pos + N]);
        hijos.push_back(nuevo);
    }
    if (col > 0) {
        string nuevo = estado;
        swap(nuevo[pos], nuevo[pos - 1]);
        hijos.push_back(nuevo);
    }
    if (col < N - 1) {
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
    bool operator>(const Nodo &otro) const { return f > otro.f; }
};

int main() {
    cin >> N;
    string inicio;
    cin >> inicio;

    
    objetivo = "";
    for (int i = 0; i < N * N - 1; i++) {
        
        if (N <= 4) objetivo += char('A' + i);   
        else objetivo += to_string(i + 1);       
    }
    objetivo += '#'; 

    if (inicio == objetivo) {
        cout << 0 << endl;
        return 0;
    }

    priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pq;
    unordered_map<string, int> costo;

    pq.push({inicio, 0, heuristica(inicio)});
    costo[inicio] = 0;

    while (!pq.empty()) {
        Nodo actual = pq.top();
        pq.pop();

        if (actual.estado == objetivo) {
            cout << actual.g << endl;
            return 0;
        }

        for (auto &hijo : generarMovimientos(actual.estado)) {
            int nuevoG = actual.g + 1;
            if (!costo.count(hijo) || nuevoG < costo[hijo]) {
                costo[hijo] = nuevoG;
                int nuevoF = nuevoG + heuristica(hijo);
                pq.push({hijo, nuevoG, nuevoF});
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
