#include "most_occurred_word.h"
#include <sstream>
#include <unordered_map>
#include <algorithm>

std::string mostOccuredWord(const std::string& line) {
    std::istringstream stream(line);
    std::unordered_map<std::string, int> wordCount;
    std::string word;
    while (stream >> word) {
        wordCount[word]++;
    }

    return std::max_element(wordCount.begin(), wordCount.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second < b.second;
        })->first;
}
