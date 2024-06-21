#pragma once
#include <string>

enum class CoffeeType: uint_fast8_t { ESPRESSO, LATTE, CAPPUCCINO };

class Coffee {
private:
    CoffeeType type;
    unsigned int cost;
public:
    explicit Coffee(CoffeeType t);
    void prepare() const;
    [[nodiscard]] unsigned int getCost() const;
};
