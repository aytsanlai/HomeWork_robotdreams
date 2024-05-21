#include <iostream>
using namespace std;

void toUppercase(char str[]) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 'a' - 'A';
        }
    }
}

int main() {
    const int MAX_SIZE = 100;
    char str[MAX_SIZE];

    cout << "Enter a string: ";
    cin.getline(str, MAX_SIZE);

    toUppercase(str);

    cout << "Transformed string: " << str << endl;

    return 0;
}