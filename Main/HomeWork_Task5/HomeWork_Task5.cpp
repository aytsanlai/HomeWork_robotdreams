#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char symbol;
    int sum = 0;

    cout << "To end program enter '.': " << endl;

    while (true) {
        cout << "Enter a character: ";
        cin >> symbol;

        if (symbol == '.') {
            cout << "Program ended." << endl;
            break;
        }
        else if (islower(symbol)) {
            symbol = toupper(symbol);
            cout << "Converted character: " << symbol << endl;
        }
        else if (isdigit(symbol)) {
            sum += symbol - '0';
            cout << "Current sum: " << sum << endl;
        }
        else {
            cout << "This character is not processed by the program." << endl;
        }
    }

    return 0;
}
