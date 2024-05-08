#include <iostream>

using namespace std;

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    int number;

    cout << "Enter a positive integer: ";
    cin >> number;

    if (number < 0) {
        cout << "Factorial is not defined for negative numbers." << endl;
        return 1;
    }

    int fact = factorial(number);
    cout << "Factorial of " << number << " is: " << fact << endl;

    return 0;
}
