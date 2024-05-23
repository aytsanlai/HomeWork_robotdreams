#include <iostream>

bool find(const int* arr, int size, int elem) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == elem) {
            return true;
        }
    }
    return false;
}

int main() {
    const int SIZE = 5;
    int arr[SIZE] = { 1, 2, 3, 4, 5 };
    int elem;

    std::cout << "Enter the number to find: ";
    std::cin >> elem;

    if (find(arr, SIZE, elem)) {
        std::cout << "Number found in the array." << std::endl;
    }
    else {
        std::cout << "Number not found in the array." << std::endl;
    }

    return 0;
}
