#include <iostream>
#include "swap.h"

using namespace std;

int main() {
    int x = 5, y = 10;
    cout << "Before swap (by reference): x = " << x << ", y = " << y << endl;
    swap(x, y);
    cout << "After swap (by reference): x = " << x << ", y = " << y << endl;

    int a = 15, b = 20;
    cout << "Before swap (by pointer): a = " << a << ", b = " << b << endl;
    swap(&a, &b);
    cout << "After swap (by pointer): a = " << a << ", b = " << b << endl;

    return 0;
}
