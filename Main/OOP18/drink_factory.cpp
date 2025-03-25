#include "drink_factory.h"
#include "drink.h"

Drink* createCoffee(CoffeeType type, SizeType size) {
    return new Coffee(type, size);
}

Drink* createTea(TeaType type, SizeType size) {
    return new Tea(type, size);
}
