#include "drink_factory.h"

Drink* createDrink(DrinkType type, SizeType size) {
    switch (type) {
    case DrinkType::ESPRESSO:
    case DrinkType::AMERICANO:
    case DrinkType::LATTE:
    case DrinkType::CAPPUCCINO:
        return new Coffee(type, size);
    case DrinkType::BLACK_TEA:
    case DrinkType::GREEN_TEA:
        return new Tea(type, size);
    default:
        return nullptr;
    }
}
