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

vector<vector<string>> moveTile(vector<vector<string>> matrix, const string &movement, int row, int col) {
    int newRow = row, newCol = col;

    if (movement == "UP" && row > 0) newRow--;
    else if (movement == "DOWN" && row < 3) newRow++;
    else if (movement == "LEFT" && col > 0) newCol--;
    else if (movement == "RIGHT" && col < 3) newCol++;
    else return matrix; 

    swap(matrix[row][col], matrix[newRow][newCol]);
    return matrix;
}

int main() {
    string tablero_tmp, movement;
    cin >> tablero_tmp;
    cin >> movement;

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

    matrix = moveTile(matrix, movement, blankRow, blankCol);
    print(matrix);

    return 0;
}
