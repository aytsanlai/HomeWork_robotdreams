#include "WordleGame.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <unordered_set>

WordleGame::WordleGame(const std::string& filePath) : attempts(0), wordOfTheDayMode(false) {
    loadDatabase(filePath);
    currentDate = getCurrentDate();
    srand(static_cast<unsigned int>(time(0)));
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

std::string WordleGame::getCurrentDate() {
    time_t now = time(nullptr);
    tm ltm;
    localtime_s(&ltm, &now);
    std::ostringstream date;
    date << std::setw(4) << std::setfill('0') << (1900 + ltm.tm_year)
        << std::setw(2) << std::setfill('0') << (1 + ltm.tm_mon)
        << std::setw(2) << std::setfill('0') << ltm.tm_mday;
    return date.str();
}

std::string WordleGame::getRandomWord() {
    int randomIndex = rand() % database.size();
    return database[randomIndex];
}

std::string WordleGame::getWordOfTheDay() {
    time_t now = time(nullptr);
    int daysSinceEpoch = static_cast<int>(now / 86400);
    int index = daysSinceEpoch % database.size();
    return database[index];
}

std::string WordleGame::compareWords(const std::string& guess) {
    std::string result = "*****";
    std::string tempTarget = targetWord;
    std::unordered_multiset<char> unmatchedTargetChars;

    for (int i = 0; i < 5; ++i) {
        if (guess[i] == targetWord[i]) {
            result[i] = toupper(guess[i]);
            tempTarget[i] = '*';
        }
        else {
            unmatchedTargetChars.insert(tempTarget[i]);
        }
    }

    for (int i = 0; i < 5; ++i) {
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
    std::ifstream file("word_of_the_day_status.txt");
    if (file.is_open()) {
        std::string date;
        file >> date;
        file.close();
        return date == getCurrentDate();
    }
    return false;
}

void WordleGame::markWordOfTheDayAsGuessed() {
    std::ofstream file("word_of_the_day_status.txt");
    file << getCurrentDate();
    file.close();
}

bool WordleGame::isValidWord(const std::string& word) {
    return word.length() == 5;
}

void WordleGame::loadDatabase(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
            if (word.length() == 5) {
                database.push_back(word);
            }
        }
        file.close();
        std::cout << "Loaded " << database.size() << " 5-letter words from the file." << std::endl;
    }
    else {
        std::cerr << "Error: Could not open the word list file." << std::endl;
    }
}

void WordleGame::displayMenu() const {
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
