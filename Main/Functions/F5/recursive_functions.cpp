#include "recursive_functions.h"
#include <iostream>

namespace RecursiveFunctions {
    void printDescendingRecursively(int count) {
        if (count == 0)
            return;
        std::cout << count << " ";
        printDescendingRecursively(count - 1);
    }

    void printAscendingRecursively(int count) {
        if (count == 0)
            return;
        printAscendingRecursively(count - 1);
        std::cout << count << " ";
    }
}
