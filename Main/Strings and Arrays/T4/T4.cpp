#include <string>
#include <cctype>
#include <iostream>

void countVowelsAndConsonants(const std::string& str, unsigned int& vowelsCount, unsigned int& consonantsCount) {
    vowelsCount = 0;
    consonantsCount = 0;
    for (char ch : str) {
        ch = static_cast<char>(std::tolower(ch));
        if (static_cast<bool>(std::isalpha(ch))) {
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                ++vowelsCount;
            }
            else {
                ++consonantsCount;
            }
        }
    }
}

void displayCounts(const unsigned int vowelsCount, const unsigned int consonantsCount) {
    std::cout << "Number of vowels: " << vowelsCount << std::endl;
    std::cout << "Number of consonants: " << consonantsCount << std::endl;
}

int main() {
    std::string  input;
    unsigned int vowels = 0, consonants = 0;

    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    if (input.empty()) {
        std::cout << "No input provided. Exiting." << std::endl;
        return 1;
    }

    countVowelsAndConsonants(input, vowels, consonants);
    displayCounts(vowels, consonants);

    return 0;
}