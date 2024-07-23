#include "unique_words_count.h"
#include <sstream>
#include <set>

unsigned int uniqueWordsCount(const std::string& line) {
    std::istringstream stream(line);
    std::set<std::string> uniqueWords;
    std::string word;
    while (stream >> word) {
        uniqueWords.insert(word);
    }
    return uniqueWords.size();
}
