#pragma once
#include <string>
#include "Game.h"

class RunawayPolicy {
public:
    virtual std::string getFullInfo() const = 0;
    virtual void apply(Game &game) = 0;
    virtual ~RunawayPolicy() = default; // Use virtual destructor for polymorphic base class
};

class Runaway_ItemEquippedRemoval : public RunawayPolicy {
public:
    std::string getFullInfo() const override {
        return "Runaway Policy: Remove an equipped item.";
    }

    void apply(Game &game) override {
        game.removeEquippedItem();
    }
};

class Runaway_ModifierFromHandRemoval : public RunawayPolicy {
public:
    std::string getFullInfo() const override {
        return "Runaway Policy: Remove a modifier from hand.";
    }

    void apply(Game &game) override {
        game.removeRandomModifierFromHand();
    }
};

class Runaway_BiggestBonusCardRemoval : public RunawayPolicy {
public:
    std::string getFullInfo() const override {
        return "Runaway Policy: Remove the biggest bonus card.";
    }

    void apply(Game &game) override {
        game.removeBiggestBonusCard();
    }
};