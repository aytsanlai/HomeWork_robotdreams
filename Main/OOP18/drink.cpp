#include "drink.h"
#include <iostream>

// Base Drink Class
Drink::Drink(DrinkType t, SizeType s) : type(t), size(s), cost(0) {}

unsigned int Drink::getCost() const {
    return cost;
}

// Coffee Class
Coffee::Coffee(DrinkType t, SizeType s) : Drink(t, s) {
    switch (type) {
    case DrinkType::ESPRESSO:
        cost = 50;
        size = SizeType::NONE; // Espresso is one size only
        break;
    case DrinkType::AMERICANO:
        cost = (size == SizeType::M) ? 40 : (size == SizeType::L) ? 60 : 80;
        break;
    case DrinkType::LATTE:
        cost = (size == SizeType::M) ? 70 : (size == SizeType::L) ? 90 : 110;
        break;
    case DrinkType::CAPPUCCINO:
        cost = (size == SizeType::M) ? 80 : 100; // Cappuccino has M and L sizes
        break;
    default:
        cost = 0;
        break;
    }
}

void Coffee::prepare() const {
    switch (type) {
    case DrinkType::ESPRESSO:
        std::cout << "Preparing Espresso: Water, Coffee, Time: 2 minutes" << std::endl;
        break;
    case DrinkType::AMERICANO:
        std::cout << "Preparing Americano: Water, Coffee, Time: 2.25 minutes" << std::endl;
        break;
    case DrinkType::LATTE:
        std::cout << "Preparing Latte: Water, Coffee, Milk, Time: 2.5 minutes" << std::endl;
        break;
    case DrinkType::CAPPUCCINO:
        std::cout << "Preparing Cappuccino: Water, Coffee, Milk, Foam, Time: 3.75 minutes" << std::endl;
        break;
    default:
        break;
    }
}

// Tea Class
Tea::Tea(DrinkType t, SizeType s) : Drink(t, s) {
    switch (type) {
    case DrinkType::BLACK_TEA:
        cost = (size == SizeType::M) ? 30 : (size == SizeType::L) ? 50 : 0;
        break;
    case DrinkType::GREEN_TEA:
        cost = (size == SizeType::M) ? 35 : (size == SizeType::L) ? 55 : 0;
        break;
    default:
        cost = 0;
        break;
    }
}

void Tea::prepare() const {
    switch (type) {
    case DrinkType::BLACK_TEA:
        std::cout << "Preparing Black Tea: Water, Tea, Time: 3 minutes" << std::endl;
        break;
    case DrinkType::GREEN_TEA:
        std::cout << "Preparing Green Tea: Water, Tea, Time: 3.25 minutes" << std::endl;
        break;
    default:
        break;
    }
}
