#pragma once
#include <string>

enum class CoffeeType { ESPRESSO, LATTE, CAPPUCCINO };

class Coffee {
private:
    CoffeeType type;
    int cost;
public:
    Coffee(CoffeeType t);
    void prepare() const;
    int getCost() const;
};
