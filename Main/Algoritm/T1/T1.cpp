#include <iostream>

bool find(int** arr_2d, int rows, int columns, int toFind) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (arr_2d[i][j] == toFind) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int rows, columns;

    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> columns;

    int** arr_2d = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        arr_2d[i] = new int[columns];
    }

    std::cout << "Enter the elements of the array:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << "Element [" << i << "][" << j << "]: ";
            std::cin >> arr_2d[i][j];
        }
    }

    int toFind;
    std::cout << "Enter the number to find: ";
    std::cin >> toFind;

    if (find(arr_2d, rows, columns, toFind)) {
        std::cout << "Number found in the array." << std::endl;
    }
    else {
        std::cout << "Number not found in the array." << std::endl;
    }

    for (int i = 0; i < rows; ++i) {
        delete[] arr_2d[i];
    }
    delete[] arr_2d;

    return 0;
}
