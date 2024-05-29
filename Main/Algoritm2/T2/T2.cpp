#include <iostream>
#include <algorithm>

const int ROWS = 3;
const int COLUMNS = 3;

enum class SortingDirection { ByRows, ByColumns };

void sort(int arr[ROWS][COLUMNS], SortingDirection direction) {
    if (direction == SortingDirection::ByRows) {
        for (int i = 0; i < ROWS; ++i) {
            std::sort(arr[i], arr[i] + COLUMNS);
        }
    }
    else if (direction == SortingDirection::ByColumns) {
        for (int j = 0; j < COLUMNS; ++j) {
            for (int i = 0; i < ROWS; ++i) {
                for (int k = i + 1; k < ROWS; ++k) {
                    if (arr[i][j] > arr[k][j]) {
                        std::swap(arr[i][j], arr[k][j]);
                    }
                }
            }
        }
    }
}

void printArray(int arr[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printMatrix(int arr[ROWS][COLUMNS]) {
    for (int j = 0; j < COLUMNS; ++j) {
        for (int i = 0; i < ROWS; ++i) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int arr[ROWS][COLUMNS] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    std::cout << "Original array:" << std::endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            std::cout << arr[i][j] << " ";
        }
    }
    std::cout << std::endl << std::endl;

    sort(arr, SortingDirection::ByRows);
    std::cout << "Sorted by rows:" << std::endl;
    printArray(arr);
    std::cout << std::endl;

    sort(arr, SortingDirection::ByColumns);
    std::cout << "Sorted by columns:" << std::endl;
    printMatrix(arr);

    return 0;
}
