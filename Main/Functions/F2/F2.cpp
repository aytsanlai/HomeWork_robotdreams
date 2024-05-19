#include <iostream>
using namespace std;

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int factorialRecursion(int n) {
    if (n <= 1) {
        return 1;
    }
    else {
        return n * factorialRecursion(n - 1);
    }
}

int main() {
    int num;
    cout << "Enter a number to calculate its factorial: ";
    cin >> num;
    cout << "Factorial (using loop) of " << num << " is: " << factorial(num) << endl;
    cout << "Factorial (using recursion) of " << num << " is: " << factorialRecursion(num) << endl;

    return 0;
}
