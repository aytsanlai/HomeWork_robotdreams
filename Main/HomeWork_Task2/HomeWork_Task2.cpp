#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n <= 1)
        return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return b;
}

int main() {
    int position;

    cout << "Enter the position of the Fibonacci sequence element: ";
    cin >> position;

    if (position < 1) {
        cout << "Position should be a positive integer." << endl;
        return 1;
    }

    int value = fibonacci(position);
    cout << "The value of the Fibonacci sequence element at position " << position << " is: " << value << endl;

    return 0;
}
