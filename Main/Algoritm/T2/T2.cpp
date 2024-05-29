#include <iostream>

enum class SortingDirection {
    ascending,
    descending
};

bool isSorted(const int* arr, int size, SortingDirection direction) {
    if (size <= 1)
        return true;

    if (direction == SortingDirection::ascending) {
        for (int i = 1; i < size; ++i) {
            if (arr[i] < arr[i - 1])
                return false;
        }
    }
    else if (direction == SortingDirection::descending) {
        for (int i = 1; i < size; ++i) {
            if (arr[i] > arr[i - 1])
                return false;
        }
    }

    return true;
}

int main() {
    int arr_asc[] = { 1, 2, 3, 4, 5 };
    int arr_desc[] = { 5, 4, 3, 2, 1 };
    int arr_mixed[] = { 1, 3, 2, 5, 4 };

    std::cout << std::boolalpha << "Ascending array is sorted: " << isSorted(arr_asc, 5, SortingDirection::ascending) << std::endl;
    std::cout << std::boolalpha << "Descending array is sorted: " << isSorted(arr_desc, 5, SortingDirection::descending) << std::endl;
    std::cout << std::boolalpha << "Mixed array is sorted: " << isSorted(arr_mixed, 5, SortingDirection::ascending) << std::endl;

    return 0;
}
