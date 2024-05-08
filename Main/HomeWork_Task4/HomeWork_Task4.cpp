#include <iostream>
using namespace std;

int main() {
    int size;
    cout << "Enter the number of rows for the figure: ";
    cin >> size;

    cout << "a) " << endl;
    for (int i = size; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "b) " << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j <= i; ++j) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "c) " << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "d) " << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            cout << "*";
        }
        for (int j = 0; j < size; ++j) {
            cout << "*";
        }
        cout << endl;
    }

    cout << "e) " << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            cout << "";
        }
        for (int j = 0; j <= i; ++j) {
            if ((size - i + j - 1) % 2 == 0)
                cout << "1";
            else
                cout << "0";
        }
        cout << endl;
    }

    return 0;
}
