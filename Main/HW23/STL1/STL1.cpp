#include <iostream>
#include <string>
#include "unique_words_count.h"
#include "most_occurred_word.h"
#include "balanced_brackets.h"
#include "has_cycle.h"

int main() {
    std::string inputLine;

    //WordsCount
    std::cout << "Enter a line for unique words count: ";
    std::getline(std::cin, inputLine);
    std::cout << "Unique words count: " << uniqueWordsCount(inputLine) << std::endl;

    //OccuredWord
    std::cout << "Enter a line to find the most occurred word: ";
    std::getline(std::cin, inputLine);
    std::cout << "Most occurred word: " << mostOccuredWord(inputLine) << std::endl;

    //BracketsBalanced
    std::cout << "Enter a line to check if brackets are balanced: ";
    std::getline(std::cin, inputLine);
    std::cout << (areBracketsBalanced(inputLine) ? "Brackets are balanced" : "Brackets are not balanced") << std::endl;

    //Ñycle
    Node* node1 = new Node{ 1, nullptr };
    Node* node2 = new Node{ 2, nullptr };
    Node* node3 = new Node{ 3, nullptr };
    node1->next = node2;
    node2->next = node3;
    node3->next = node1;
    std::cout << "Has cycle: " << (has_cycle(node1) ? "Yes" : "No") << std::endl;

    //Memory
    node3->next = nullptr;
    delete node1;
    delete node2;
    delete node3;

    return 0;
}
