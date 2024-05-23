#include <iostream>
#include "cyclic_functions.h"
#include "recursive_functions.h"

using namespace std;
using namespace CyclicFunctions;
using namespace RecursiveFunctions;

int main() {
    float radius;
    cout << "Enter the radius of the circle: ";
    cin >> radius;

    cout << "Area of the circle: " << getArea(radius) << endl;
    cout << "Circumference of the circle: " << getCircumference(radius) << endl;

    int n;
    cout << "Enter the count of natural numbers: ";
    cin >> n;

    cout << "Descending (recursion): ";
    printDescendingRecursively(n);
    cout << endl;

    cout << "Ascending (recursion): ";
    printAscendingRecursively(n);
    cout << endl;

    return 0;
}
