#include "Coffee.h"
#include <iostream>

Coffee::Coffee(CoffeeType t) : type(t) {
    switch (type) {
    case CoffeeType::ESPRESSO:
        cost = 50;
        break;
    case CoffeeType::LATTE:
        cost = 70;
        break;
    case CoffeeType::CAPPUCCINO:
        cost = 80;
        break;
    }
}

void Coffee::prepare() const {
    std::string coffeeName;
    switch (type) {
    case CoffeeType::ESPRESSO:
        coffeeName = "Espresso";
        std::cout << "Preparing " << coffeeName << ": Water, Coffee, Time: 2 minutes\n";
        break;
    case CoffeeType::LATTE:
        coffeeName = "Latte";
        std::cout << "Preparing " << coffeeName << ": Water, Coffee, Milk, Time: 2,5 minutes\n";
        break;
    case CoffeeType::CAPPUCCINO:
        coffeeName = "Cappuccino";
        std::cout << "Preparing " << coffeeName << ": Water, Coffee, Milk, Foam, Time: 3,75 minutes\n";
        break;
    }
}

int Coffee::getCost() const {
    return cost;
}
