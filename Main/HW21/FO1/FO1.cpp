#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//a:
bool compareByLength(const std::string& a, const std::string& b) {
    return a.length() < b.length();
}

//b:
class LengthComparator {
public:
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() < b.length();
    }
};

int main() {
    std::vector<std::string> stringContainer = { "aaaaa", "bb", "ccc", "d", "eeee" };

    std::sort(stringContainer.begin(), stringContainer.end(), compareByLength);

    std::cout << "Sorted by length (simple function): ";
    for (const auto& str : stringContainer) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    std::sort(stringContainer.begin(), stringContainer.end(), LengthComparator());

    std::cout << "Sorted by length (functor): ";
    for (const auto& str : stringContainer) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    std::sort(stringContainer.begin(), stringContainer.end(),
        [](const std::string& a, const std::string& b) {
            return a.length() < b.length();
        });

    std::cout << "Sorted by length (lambda function): ";
    for (const auto& str : stringContainer) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}
