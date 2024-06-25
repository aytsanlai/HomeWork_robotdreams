#include <iostream>
#include "drink_shop.h"

int main() {
    CoffeeShop shop("CoffeeBreak");

    int table = shop.takePlace();
    if (table != -1) {
        std::cout << "Table " << table << " is occupied.\n";
        shop.order(table);
        if (shop.prepare(table)) {
            std::cout << "Drink prepared for table " << table << ".\n";
        }
        if (shop.getReceipt(table)) {
            std::cout << "Receipt processed for table " << table << ".\n";
        }
    }
    else {
        std::cout << "No available tables.\n";
    }

    return 0;
}
