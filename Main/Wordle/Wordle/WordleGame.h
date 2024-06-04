#ifndef WORDLEGAME_H
#define WORDLEGAME_H

#include <string>
#include <vector>
#include <unordered_set>

class WordleGame {
private:
    std::vector<std::string> database;
    std::string targetWord;
    std::string currentDate;
    int attempts;
    bool wordOfTheDayMode;
    std::vector<std::string> pastAttempts;
    std::unordered_set<std::string> validWords;

    std::string getCurrentDate();
    std::string getRandomWord();
    std::string getWordOfTheDay();
    std::string compareWords(const std::string& guess);
    bool isWordOfTheDayGuessed();
    void markWordOfTheDayAsGuessed();
    bool isValidWord(const std::string& word);
    void loadDatabase();
    void displayMenu() const;
    void resetGame();
    void play();
    void displayPastAttempts() const;

public:
    WordleGame();
    void start();
};

#endif // WORDLEGAME_H
