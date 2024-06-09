#include <iostream>
#include <iomanip>
#include "row_major_order.h"

#define MIN_SIZE uint_fast8_t

using namespace std;

void rowMajorOrder(int arr[ROWS][COLS]) {
    for (MIN_SIZE row = 0; row < ROWS; ++row) {
        const bool go_left = row % 2 == 0;

        for (MIN_SIZE col = 0; col < COLS; ++col) {
            cout << std::setw(2) << std::setfill(' ') << arr[ROWS - row - 1][go_left ? (COLS - col - 1) : col] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    int arr[ROWS][COLS] = {
        { 1,  2,  3,  4 },
        { 5,  6,  7,  8 },
        { 9, 10, 11, 12 },
        {13, 14, 15, 16 }
    };

    rowMajorOrder(arr);

    return 0;
}
