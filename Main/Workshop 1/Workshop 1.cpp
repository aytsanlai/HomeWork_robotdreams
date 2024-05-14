#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int determineWinner(char userChoice, char computerChoice) {
    if (userChoice == computerChoice)
        return 0;
    if ((userChoice == 'r' && computerChoice == 's') || (userChoice == 'p' && computerChoice == 'r') || (userChoice == 's' && computerChoice == 'p'))
        return 1;
    return -1;
}

int main() {
    srand(time(0));

    int rounds;
    int userWins = 0, computerWins = 0, draws = 0;
    char symbols[] = { 'r', 'p', 's' };

    cout << "Hello! Welcome to 'Rock paper scissors' game for 2 players." << endl;

    do {
        cout << "Enter rounds number (-1 to quit): ";
        cin >> rounds;
        if (rounds == -1)
            break;

        for (int i = 0; i < rounds; ++i) {
            char userChoice, computerChoice;

            cout << "To make your turn, enter one of possible symbols:\n";
            cout << "r - rock\n";
            cout << "p - paper\n";
            cout << "s - scissors\n";
            cout << "Your choice is ";
            cin >> userChoice;

            int randomIndex = rand() % 3;
            computerChoice = symbols[randomIndex];
            cout << "PC choice is " << (char)toupper(computerChoice) << endl;

            int result = determineWinner(userChoice, computerChoice);
            if (result == 1) {
                cout << "You WIN\n";
                ++userWins;
            }
            else if (result == -1) {
                cout << "You LOST\n";
                ++computerWins;
            }
            else {
                cout << "It's a draw\n";
                ++draws;
            }
        }

        cout << "Thanks for playing. Your final stats:\n";
        cout << "number of rounds - " << rounds << endl;
        cout << "number of wins - " << userWins << endl;
        cout << "number of losses - " << computerWins << endl;
        cout << "number of draws - " << draws << endl;
        if (userWins > computerWins)
            cout << "--You're smarter than my PC algo!-" << endl;

        userWins = 0;
        computerWins = 0;
        draws = 0;

    } while (rounds != -1);

    cout << "BYE-BYE" << endl;

    return 0;
}
