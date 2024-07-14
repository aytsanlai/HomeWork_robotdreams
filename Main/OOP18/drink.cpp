#include "drink.h"
#include <iostream>

// Base Drink Class
Drink::Drink(SizeType s) : size(s), cost(0) {}

unsigned int Drink::getCost() const {
    return cost;
}

// Coffee Class
Coffee::Coffee(CoffeeType t, SizeType s) : Drink(s), type(t) {
    switch (type) {
    case CoffeeType::ESPRESSO:
        cost = 50;
        size = SizeType::NONE;
        break;
    case CoffeeType::AMERICANO:
        cost = (size == SizeType::M) ? 40 : (size == SizeType::L) ? 60 : 80;
        break;
    case CoffeeType::LATTE:
        cost = (size == SizeType::M) ? 70 : (size == SizeType::L) ? 90 : 110;
        break;
    case CoffeeType::CAPPUCCINO:
        cost = (size == SizeType::M) ? 80 : 100;
        break;
    default:
        cost = 0;
        break;
    }
}

void Coffee::prepare() const {
    switch (type) {
    case CoffeeType::ESPRESSO:
        std::cout << "Preparing Espresso: Water, Coffee, Time: 2 minutes" << std::endl;
        break;
    case CoffeeType::AMERICANO:
        std::cout << "Preparing Americano: Water, Coffee, Time: 2.25 minutes" << std::endl;
        break;
    case CoffeeType::LATTE:
        std::cout << "Preparing Latte: Water, Coffee, Milk, Time: 2.5 minutes" << std::endl;
        break;
    case CoffeeType::CAPPUCCINO:
        std::cout << "Preparing Cappuccino: Water, Coffee, Milk, Foam, Time: 3.75 minutes" << std::endl;
        break;
    default:
        break;
    }
}

// Tea Class
Tea::Tea(TeaType t, SizeType s) : Drink(s), type(t) {
    switch (type) {
    case TeaType::BLACK_TEA:
        cost = (size == SizeType::M) ? 30 : (size == SizeType::L) ? 50 : 0;
        break;
    case TeaType::GREEN_TEA:
        cost = (size == SizeType::M) ? 35 : (size == SizeType::L) ? 55 : 0;
        break;
    default:
        cost = 0;
        break;
    }
}

void Tea::prepare() const {
    switch (type) {
    case TeaType::BLACK_TEA:
        std::cout << "Preparing Black Tea: Water, Tea, Time: 3 minutes" << std::endl;
        break;
    case TeaType::GREEN_TEA:
        std::cout << "Preparing Green Tea: Water, Tea, Time: 3.25 minutes" << std::endl;
        break;
    default:
        break;
    }
}
