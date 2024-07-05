#include <iostream>
#include "VictoryPolicy.h"
#include "Game.h"

class LevelUpPolicy : public VictoryPolicy {
public:
    void apply(Game &game) override {
        game.addPlayerLevel(2);
        std::cout << "Level up by several points!" << std::endl;
    }
};

class NewCardPolicy : public VictoryPolicy {
public:
    void apply(Game &game) override {
        std::cout << "Generate new cards in hand!" << std::endl;
    }
};

class NewOutfitPolicy : public VictoryPolicy {
public:
    void apply(Game &game) override {
        std::cout << "Generate a new outfit!" << std::endl;
    }
};