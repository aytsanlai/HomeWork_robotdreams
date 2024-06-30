#pragma once
#include "RunawayPolicy.h"

class BasicRunawayPolicy : public RunawayPolicy {
public:
    std::string getFullInfo() const override {
        return "You are dead! (level is dropped to 1, will lose 3 cards from the hand)";
    }
};

class Runaway_ItemEquipedRemoval : public RunawayPolicy {
public:
    std::string getFullInfo() const override {
        return "You will lose an equipped item.";
    }
};

class Runaway_ModifierFromHandRemoval : public RunawayPolicy {
public:
    std::string getFullInfo() const override {
        return "You will lose a modifier from your hand.";
    }
};

class Runaway_BiggestBonusCardRemoval : public RunawayPolicy {
public:
    std::string getFullInfo() const override {
        return "You will lose the card with the biggest bonus.";
    }
};
