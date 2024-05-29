#include <iostream>
#include "column_major_order.h"

using namespace std;

void columnMajorOrder(int arr[ROWS][COLS]) {
    for (int j = 0; j < COLS; ++j) {
        for (int i = 0; i < ROWS; ++i) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int arr[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    cout << "Column-major order traversal:" << endl;
    columnMajorOrder(arr);

    return 0;
}
