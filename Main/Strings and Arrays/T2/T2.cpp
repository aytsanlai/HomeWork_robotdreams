#include <iostream>
#include <string>
#include <cctype>

void toUppercase(std::string& str) {
    for (char& ch : str) {
        if (static_cast<bool>(std::islower(ch))) {
            ch = static_cast<char>(std::toupper(ch));
        }
    }
}

int main() {
    std::string str;

    std::cout << "Enter a string: ";
    std::getline(std::cin, str);

    toUppercase(str);

    std::cout << "Transformed string: " << str << std::endl;

    return 0;
}