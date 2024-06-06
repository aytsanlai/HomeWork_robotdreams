#include "WordleGame.h"
#include <iostream>

int main() {
    std::string filePath = "words.txt";
    WordleGame game(filePath);
    game.start();
    return 0;
}
