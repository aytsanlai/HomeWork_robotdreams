#include "WordleGame.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <unordered_set>
#include <algorithm>

constexpr uint_fast8_t WORD_LENGTH = 5;

WordleGame::WordleGame(const std::string& filePath) : attempts(0), wordOfTheDayMode(false) {
    loadDatabase(filePath);
    srand(static_cast<unsigned int>(time(nullptr)));
}

void WordleGame::start() {
    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            if (isWordOfTheDayGuessed()) {
                std::cout << "Already found! Come back tomorrow!\n";
                continue;
            }
            targetWord = getWordOfTheDay();
            wordOfTheDayMode = true;
        }
        else if (choice == 2) {
            targetWord = getRandomWord();
            wordOfTheDayMode = false;
        }
        else {
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

        resetGame();
        play();
    }
}

uint_fast16_t WordleGame::getCurrentDate() {
    constexpr uint_fast8_t  SECONDS_IN_MINUTE = 60;
    constexpr uint_fast8_t  MINUTES_IN_HOUR = 60;
    constexpr uint_fast8_t  HOURS_IN_DAY = 24;
    constexpr uint_fast32_t SECONDS_IN_DAY = SECONDS_IN_MINUTE * MINUTES_IN_HOUR * HOURS_IN_DAY;
    std::time(nullptr);
    const time_t now = time(nullptr);

   
    tm localTime{};
    localtime_s( &localTime, &now);

    return mktime(&localTime) / SECONDS_IN_DAY;
}

std::string WordleGame::getRandomWord() {
    const size_t randomIndex = rand() % database.size();
    return database[randomIndex];
}

std::string WordleGame::getWordOfTheDay() {
    const uint_fast16_t todayIndex = WordleGame::getCurrentDate() % database.size();
    return database[todayIndex];
}

std::string WordleGame::compareWords(const std::string& guess) {
    std::string                   result = "*****";
    std::string                   tempTarget = targetWord;
    std::unordered_multiset<char> unmatchedTargetChars;

    for (uint_fast8_t i = 0; i < WORD_LENGTH; ++i) {
        if (guess[i] == targetWord[i]) {
            result[i] = toupper(guess[i]);
            tempTarget[i] = '*';
        }
        else {
            unmatchedTargetChars.insert(tempTarget[i]);
        }
    }

    for (uint_fast8_t i = 0; i < WORD_LENGTH; ++i) {
        if (result[i] == '*') {
            auto it = unmatchedTargetChars.find(guess[i]);
            if (it != unmatchedTargetChars.end()) {
                result[i] = tolower(guess[i]);
                unmatchedTargetChars.erase(it);
            }
        }
    }

    return result;
}

bool WordleGame::isWordOfTheDayGuessed() {
    std::ifstream file("word_of_the_day_status.txt", std::ios::binary);
    if (file.is_open()) {
        uint_fast16_t date;
        file.read(reinterpret_cast<char*>(&date), sizeof(date));
        file.close();
        return date == getCurrentDate();
    }
    return false;
}

void WordleGame::markWordOfTheDayAsGuessed() {
    std::ofstream file("word_of_the_day_status.txt", std::ios::binary | std::ios::trunc);
    if (file.is_open()) {
        uint_fast16_t date = getCurrentDate();
        file.write(reinterpret_cast<const char*>(&date), sizeof(date));
        file.close();
    }
}

bool WordleGame::isValidWord(const std::string& word) {
    return word.length() == WORD_LENGTH;
}

void WordleGame::loadDatabase(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
            if (word.length() == WORD_LENGTH) {
                database.push_back(word);
            }
        }
        file.close();
    }
    else {
        std::cerr << "Error: Could not open the word list file." << std::endl;
    }
}

void WordleGame::displayMenu() {
    std::cout << "============================\n";
    std::cout << "       Welcome to Wordle!\n";
    std::cout << "============================\n";
    std::cout << "1 - Wordle of the day\n";
    std::cout << "2 - Random Wordle\n";
    std::cout << "0 - Exit\n";
    std::cout << "Enter: ";
}

void WordleGame::resetGame() {
    attempts = 0;
    pastAttempts.clear();
}

void WordleGame::play() {
    std::string guess;
    std::cout << "Start guessing the word!\n";
    while (true) {
        std::cout << "Enter a 5-letter word: ";
        std::cin >> guess;
        std::transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

        if (!isValidWord(guess)) {
            std::cout << "Please enter a valid 5-letter word.\n";
            continue;
        }

        attempts++;
        std::string result = compareWords(guess);
        pastAttempts.push_back(result);

        displayPastAttempts();

        if (result == targetWord) {
            std::cout << "That's right! You made " << attempts << " tries!\n";
            if (wordOfTheDayMode) {
                markWordOfTheDayAsGuessed();
            }
            break;
        }
    }
}

void WordleGame::displayPastAttempts() const {
    std::cout << "Past attempts:\n";
    for (const auto& attempt : pastAttempts) {
        std::cout << attempt << "\n";
    }
    std::cout << "============================\n";
}