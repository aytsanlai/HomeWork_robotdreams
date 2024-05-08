#include <iostream>
using namespace std;

int main() {
    float first;
    float difference;
    int last;

    cout << "Enter the first element of the arithmetic progression: ";
    cin >> first;
    cout << "Enter the common difference of the arithmetic progression: ";
    cin >> difference;
    cout << "Enter the number of terms in the arithmetic progression: ";
    cin >> last;

    cout << "Result:" << endl;
    for (unsigned int i = 0; i < last; ++i) {
        const float term = first + (i * difference);
        cout << term << endl;
    }

    return 0;
}


