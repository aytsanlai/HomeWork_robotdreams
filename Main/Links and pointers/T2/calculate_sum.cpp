#include "calculate_sum.h"

bool calculateSum(const double* arr, int arrSize, double& sum) {
    if (arrSize <= 0) {
        return false;
    }

    sum = 0;
    for (int i = 0; i < arrSize; ++i) {
        sum += arr[i];
    }

    return true;
}
