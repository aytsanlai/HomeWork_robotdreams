#include <iostream>
#include <array>
#include <limits>

#define SIZE_TYPE uint_fast8_t

constexpr SIZE_TYPE SIZE = 10;

void translateArray(std::array<int, SIZE>& numbers) {
    for (auto& number : numbers) {
        if (number > 0) {
            number *= 2;
        }
        else if (number < 0) {
            number = 0;
        }
    }
}

int main() {
    std::array<int, SIZE> numbers{};

    std::cout << "Enter 10 integers for the array:" << std::endl;

    for (SIZE_TYPE i = 0; i < SIZE; ++i) {
        while (true) {
            std::cout << "Element " << i + 1 << ": ";
            if (std::cin >> numbers[i]) {
                break;
            }
            else {
                std::cout << "Invalid input. Please enter an integer." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    translateArray(numbers);

    std::cout << "Transformed array:" << std::endl;
    for (const auto number : numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;

    return 0;
}