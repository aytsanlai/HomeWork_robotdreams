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
    switch (type) {
    case CoffeeType::ESPRESSO:
        std::cout << "Preparing Espresso: Water, Coffee, Time: 2 minutes" << std::endl;
        break;
    case CoffeeType::LATTE:
        std::cout << "Preparing Latte: Water, Coffee, Milk, Time: 2,5 minutes" << std::endl;
        break;
    case CoffeeType::CAPPUCCINO:
        std::cout << "Preparing Cappuccino: Water, Coffee, Milk, Foam, Time: 3,75 minutes" << std::endl;
        break;
    }
}

unsigned int Coffee::getCost() const {
    return cost;
}
