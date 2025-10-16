#include <iostream>
#include <vector>
#include <string>
using namespace std;

void print(const vector<vector<string>> &matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << matrix[i][j];
            if (j < 3) cout << " ";
        }
        cout << endl;
    }
}
void valid(const vector<vector<string>> &matrix) {
    vector<string> valid;
    int fila = -1, columna = -1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] == "#") {
                fila = i;
                columna = j;
            }
        }
    }

    if (fila > 0) valid.push_back("UP");
    if (fila < 3) valid.push_back("DOWN");
    if (columna > 0) valid.push_back("LEFT");
    if (columna < 3) valid.push_back("RIGHT");

    for (int i = 0; i < valid.size(); i++) {
        cout << valid[i] << "\n";
    }
}


int main() {
    string tablero_tmp, movement;
    cin >> tablero_tmp;

    vector<vector<string>> matrix(4, vector<string>(4));
    int row = 0, col = 0;
    int blankRow = -1, blankCol = -1;

    for (int i = 0; i < 16; i++) {
        matrix[row][col] = string(1, tablero_tmp[i]);
        if (tablero_tmp[i] == '#') {
            blankRow = row;
            blankCol = col;
        }
        col++;
        if (col == 4) { col = 0; row++; }
    }

    valid(matrix);

    return 0;
}
