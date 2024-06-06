#pragma once

#include <string>
#include <vector>
#include <unordered_set>

class WordleGame {
private:
    std::vector<std::string> database;
    std::string targetWord;
    int attempts;
    bool wordOfTheDayMode;
    std::vector<std::string> pastAttempts;

    static uint_fast16_t getCurrentDate();
    std::string getRandomWord();
    std::string getWordOfTheDay();
    std::string compareWords(const std::string& guess);
    static bool isWordOfTheDayGuessed();
    static void markWordOfTheDayAsGuessed();
    static bool isValidWord(const std::string& word);
    void loadDatabase(const std::string& filePath);
    static void displayMenu();
    void resetGame();
    void play();
    void displayPastAttempts() const;

public:
    explicit WordleGame(const std::string& filePath);
    void start();
};