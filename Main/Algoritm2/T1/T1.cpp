#include <iostream>
#include <algorithm>

void bubbleSort(int arr[], const int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    const int size = std::size(arr);

    std::cout << "Unsorted array: ";
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    bubbleSort(arr, size);

    std::cout << "Sorted array: ";
    std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}
