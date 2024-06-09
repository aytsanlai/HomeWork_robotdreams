#include <iostream>
#include <iomanip>
#include "column_major_order.h"

#define MIN_SIZE uint_fast8_t

using namespace std;

void columnMajorOrder(int arr[ROWS][COLS]) {
    for (MIN_SIZE col = 0; col < COLS; ++col) {
        for (MIN_SIZE row = 0; row < ROWS; ++row) {
            cout << std::setw(2) << std::setfill(' ') << arr[row][COLS - 1 - col] << " ";
        }
        cout << "\n";
    }
    cout << flush;
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