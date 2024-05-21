#include <iostream>
#include <limits>

using namespace std;

void translateArray(int numbers[], int size) {
    for (int i = 0; i < size; ++i) {
        if (numbers[i] > 0) {
            numbers[i] *= 2;
        }
        else if (numbers[i] < 0) {
            numbers[i] = 0;
        }
    }
}

int main() {
    const int SIZE = 10;
    int numbers[SIZE];

    cout << "Enter 10 integers for the array:" << endl;

    for (int i = 0; i < SIZE; ++i) {
        while (true) {
            cout << "Element " << i + 1 << ": ";
            if (cin >> numbers[i]) {
                break;
            }
            else {
                cout << "Invalid input. Please enter an integer." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    translateArray(numbers, SIZE);

    cout << "Transformed array:" << endl;
    for (int i = 0; i < SIZE; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}
