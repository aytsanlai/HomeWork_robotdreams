#include <iostream>
using namespace std;

bool isEqual(const char str1[], const char str2[]) {
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

int main() {
    const int MAX_SIZE = 100;
    char str1[MAX_SIZE];
    char str2[MAX_SIZE];

    cout << "Enter the first string: ";
    cin.getline(str1, MAX_SIZE);

    cout << "Enter the second string: ";
    cin.getline(str2, MAX_SIZE);

    if (isEqual(str1, str2)) {
        cout << "The strings are equal." << endl;
    }
    else {
        cout << "The strings are not equal." << endl;
    }

    return 0;
}