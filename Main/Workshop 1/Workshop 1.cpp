#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum class Symbol {
    ROCK = 'r',
    PAPER = 'p',
    SCISSORS = 's'
};

enum class Result {
    WIN,
    LOSE,
    DRAW
};

Result determineWinner(Symbol userChoice, Symbol computerChoice) {
    if (userChoice == computerChoice)
        return Result::DRAW;
    if ((userChoice == Symbol::ROCK && computerChoice == Symbol::SCISSORS) ||
        (userChoice == Symbol::PAPER && computerChoice == Symbol::ROCK) ||
        (userChoice == Symbol::SCISSORS && computerChoice == Symbol::PAPER))
        return Result::WIN;
    return Result::LOSE;
}

string symbolToString(Symbol symbol) {
    switch (symbol) {
    case Symbol::ROCK:
        return "rock";
    case Symbol::PAPER:
        return "paper";
    case Symbol::SCISSORS:
        return "scissors";
    default:
        return "unknown";
    }
}

int main() {
    srand(time(nullptr));

    int rounds;
    int userWins = 0, computerWins = 0, draws = 0;
    constexpr char symbols[] = { 'r', 'p', 's' };

    cout << "Hello! Welcome to 'Rock paper scissors' game for 2 players." << endl;

    do {
        cout << "Enter rounds number (-1 to quit): ";
        cin >> rounds;
        if (rounds == -1)
            break;

        for (unsigned int i = 0; i < rounds; ++i) {

            cout << "To make your turn, enter one of possible symbols:\n";
            cout << "r - rock\n";
            cout << "p - paper\n";
            cout << "s - scissors\n";
            cout << "Your choice is ";
            char userInput;
            cin >> userInput;

            const auto userChoice = static_cast<Symbol>(userInput);
            const auto computerChoice = static_cast<Symbol>(symbols[rand() % 3]);

            cout << "PC choice is " << symbolToString(computerChoice) << endl;

            const Result result = determineWinner(userChoice, computerChoice);
            switch (result) {
            case Result::WIN:
                cout << "You WIN\n";
                ++userWins;
                break;
            case Result::LOSE:
                cout << "You LOST\n";
                ++computerWins;
                break;
            case Result::DRAW:
                cout << "It's a draw\n";
                ++draws;
                break;
            }
        }

        cout << "Thanks for playing. Your final stats:\n";
        cout << "number of rounds - " << rounds << endl;
        cout << "number of wins - " << userWins << endl;
        cout << "number of losses - " << computerWins << endl;
        cout << "number of draws - " << draws << endl;
        if (userWins > computerWins) cout << "--You're smarter than my PC algo!-" << endl;

        userWins = computerWins = draws = 0;
    } while (rounds != -1);

    cout << "BYE-BYE" << endl;

    return 0;
}