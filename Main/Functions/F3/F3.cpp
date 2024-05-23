#include <iostream>

using namespace std;

void printDescending(int count) {
    for (int i = count; i >= 1; --i) {
        cout << i << " ";
    }
    cout << endl;
}

void printAscending(int count) {
    for (int i = 1; i <= count; ++i) {
        cout << i << " ";
    }
    cout << endl;
}

void printDescendingRecursively(int count) {
    if (count == 0)
        return;
    cout << count << " ";
    printDescendingRecursively(count - 1);
}

void printAscendingRecursively(int count) {
    if (count == 0)
        return;
    printAscendingRecursively(count - 1);
    cout << count << " ";
}

int main() {
    int n;
    cout << "Enter the count of natural numbers: ";
    cin >> n;

    cout << "Descending (loop): ";
    printDescending(n);

    cout << "Ascending (loop): ";
    printAscending(n);

    cout << "Descending (recursion): ";
    printDescendingRecursively(n);
    cout << endl;

    cout << "Ascending (recursion): ";
    printAscendingRecursively(n);
    cout << endl;

    return 0;
}
