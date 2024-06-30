#include <iostream>
#include "Game.h"
#include "ModifierDeck.h"

int main() {
    Game game;
    game.start();

    ModifierDeck deck; // Ensure ModifierDeck is declared after the header is included
    auto modifier = deck.generateModifier();
    if (modifier) {
        std::cout << "Generated modifier: " << modifier->getName() << std::endl;
    }
    else {
        std::cout << "No modifier generated." << std::endl;
    }

    return 0;
}
