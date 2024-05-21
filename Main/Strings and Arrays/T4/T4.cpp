#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

void countVowelsAndConsonants(const char str[], int& vowelsCount, int& consonantsCount) {
    vowelsCount = 0;
    consonantsCount = 0;
    int length = strlen(str);
    for (int i = 0; i < length; ++i) {
        char ch = tolower(str[i]);
        if (isalpha(ch)) {
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                ++vowelsCount;
            }
            else {
                ++consonantsCount;
            }
        }
    }
}

void displayCounts(int vowelsCount, int consonantsCount) {
    cout << "Number of vowels: " << vowelsCount << endl;
    cout << "Number of consonants: " << consonantsCount << endl;
}

int main() {
    const int MAX_SIZE = 100;
    char input[MAX_SIZE];
    int vowels = 0, consonants = 0;

    cout << "Enter a string (max " << MAX_SIZE - 1 << " characters): ";
    cin.getline(input, MAX_SIZE);

    if (strlen(input) == 0) {
        cout << "No input provided. Exiting..." << endl;
        return 1;
    }

    countVowelsAndConsonants(input, vowels, consonants);
    displayCounts(vowels, consonants);

    return 0;
}