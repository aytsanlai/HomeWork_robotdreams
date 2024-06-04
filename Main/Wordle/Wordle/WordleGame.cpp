#include "WordleGame.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>

WordleGame::WordleGame() : attempts(0), wordOfTheDayMode(false) {
    loadDatabase();
    currentDate = getCurrentDate();
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
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::ostringstream date;
    date << std::setw(4) << std::setfill('0') << (1900 + ltm->tm_year)
        << std::setw(2) << std::setfill('0') << (1 + ltm->tm_mon)
        << std::setw(2) << std::setfill('0') << ltm->tm_mday;
    return date.str();
}

std::string WordleGame::getRandomWord() {
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % database.size();
    return database[randomIndex];
}

std::string WordleGame::getWordOfTheDay() {
    int index = std::hash<std::string>{}(currentDate) % database.size();
    return database[index];
}

std::string WordleGame::compareWords(const std::string& guess) {
    std::string result = "*****";
    std::string tempTarget = targetWord;

    for (int i = 0; i < 5; ++i) {
        if (guess[i] == targetWord[i]) {
            result[i] = toupper(guess[i]);
            tempTarget[i] = '*'; // Mark matched character to avoid duplicate matches
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (result[i] == '*') {
            size_t pos = tempTarget.find(guess[i]);
            if (pos != std::string::npos) {
                result[i] = tolower(guess[i]);
                tempTarget[pos] = '*'; // Mark matched character to avoid duplicate matches
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
        return date == currentDate;
    }
    return false;
}

void WordleGame::markWordOfTheDayAsGuessed() {
    std::ofstream file("word_of_the_day_status.txt");
    file << currentDate;
    file.close();
}

bool WordleGame::isValidWord(const std::string& word) {
    return validWords.find(word) != validWords.end();
}

void WordleGame::loadDatabase() {
    database = { "HELLO", "COCON", "SPEAK", "CYCLE", "CHESS", "GAMES", "WORDS", "SMART", "CLEVER" };
    validWords.insert(database.begin(), database.end());
}

void WordleGame::displayMenu() const {
    std::cout << "============================\n";
    std::cout << "       Welcome to Wordle!\n";
    std::cout << "============================\n";
    std::cout << "1 – Wordle of the day\n";
    std::cout << "2 – Random Wordle\n";
    std::cout << "0 – Exit\n";
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

        if (guess.length() != 5 || !isValidWord(guess)) {
            std::cout << "Please enter a valid 5-letter word from the database.\n";
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
