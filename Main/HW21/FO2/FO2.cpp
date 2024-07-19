#include <iostream>
#include <vector>
#include <algorithm>

unsigned int countDivisibleBy(const std::vector<int>& vec, int number) {
    return std::count_if(vec.begin(), vec.end(),
        [number](int element) {
            return (element % number) == 0;
        });
}

int main() {

    std::vector<int> numbers = { 10, 20, 30, 15, 25, 35, 40, 50 };
    int divisor = 5;

    unsigned int count = countDivisibleBy(numbers, divisor);

    std::cout << "Count of numbers divisible by " << divisor << ": " << count << std::endl;

    return 0;
}
