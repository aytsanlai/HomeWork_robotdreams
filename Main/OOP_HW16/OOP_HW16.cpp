#include <iostream>
#include "rectangle.h"
#include "coffee.h"
#include "coffee_shop.h"

int main() {
    // Rectangle
    Rectangle rect1;
    Rectangle rect2(3.5, 4.5);
    std::cout << "Rectangle 1 - Area: " << rect1.getArea() << ", Perimeter: " << rect1.getPerimeter() << '\n';
    std::cout << "Rectangle 2 - Area: " << rect2.getArea() << ", Perimeter: " << rect2.getPerimeter() << '\n';

    // CoffeeShop 
    CoffeeShop shop("CoffeeBreak");

    int table = shop.takePlace();
    if (table != -1) {
        std::cout << "Table " << table << " is occupied.\n";
        shop.order(table);
        if (shop.prepare(table)) {
            std::cout << "Coffee prepared for table " << table << ".\n";
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
