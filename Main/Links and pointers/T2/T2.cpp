#include <iostream>
#include "calculate_sum.h"

int main() {
    const int SIZE = 5;
    double arr[SIZE] = { 1.2, 2.3, 3.4, 4.5, 5.6 };
    double sum = 0;

    if (calculateSum(arr, SIZE, sum)) {
        std::cout << "Sum of array elements: " << sum << std::endl;
    }
    else {
        std::cout << "Array size must be greater than 0" << std::endl;
    }

    return 0;
}
