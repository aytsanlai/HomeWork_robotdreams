#include <iostream>

using namespace std;

void countNumbers(int n) {
    int positive = 0, negative = 0, zeroes = 0;
    int num;

    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; ++i) {
        cin >> num;

        if (num > 0) {
            ++positive;
        }
        else if (num < 0) {
            ++negative;
        }
        else {
            ++zeroes;
        }
    }

    cout << "Positive: " << positive << ", Negative: " << negative << ", Zeroes: " << zeroes << endl;
}

int main() {
    int n;

    cout << "Enter the number of inputs: ";
    cin >> n;
    countNumbers(n);

    return 0;
}
