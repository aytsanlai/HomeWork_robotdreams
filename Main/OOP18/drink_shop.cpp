#include "drink_shop.h"
#include "drink_factory.h"
#include <iostream>
#include <utility>

CoffeeShop::CoffeeShop(std::string shopName) {
    name = std::move(shopName);
    for (TableSizeType i = 0; i < TABLES_COUNT; ++i) {
        m_Tables[i] = false;
        m_Orders[i] = nullptr;
    }
}

int CoffeeShop::takePlace() {
    for (TableSizeType i = 0; i < TABLES_COUNT; ++i) {
        if (!m_Tables[i]) {
            m_Tables[i] = true;
            return i;
        }
    }
    return -1;
}

void CoffeeShop::order(int tableNumber) {
    if (tableNumber < 0 || tableNumber >= TABLES_COUNT) {
        std::cout << "Invalid table number.\n";
        return;
    }

    if (m_Orders[tableNumber] != nullptr) {
        std::cout << "Table already has an order.\n";
        return;
    }

    std::cout << "Choose a drink type:\n";
    std::cout << "1. Coffee\n";
    std::cout << "2. Tea\n";
    unsigned int drinkChoice;
    std::cin >> drinkChoice;

    if (drinkChoice == 1) {
        std::cout << "Choose a coffee type:\n";
        std::cout << "1. Espresso\n";
        std::cout << "2. Americano\n";
        std::cout << "3. Latte\n";
        std::cout << "4. Cappuccino\n";
        unsigned int coffeeChoice;
        std::cin >> coffeeChoice;

        CoffeeType type;
        SizeType size = SizeType::NONE;

        switch (coffeeChoice) {
        case 1:
            type = CoffeeType::ESPRESSO;
            size = SizeType::NONE;
            break;
        case 2:
            type = CoffeeType::AMERICANO;
            break;
        case 3:
            type = CoffeeType::LATTE;
            break;
        case 4:
            type = CoffeeType::CAPPUCCINO;
            break;
        default:
            std::cout << "Invalid choice.\n";
            return;
        }

        if (type != CoffeeType::ESPRESSO) {
            std::cout << "Choose a size:\n";
            std::cout << "1. M\n";
            std::cout << "2. L\n";
            if (type != CoffeeType::CAPPUCCINO) {
                std::cout << "3. XL\n";
            }
            unsigned int sizeChoice;
            std::cin >> sizeChoice;

            switch (sizeChoice) {
            case 1:
                size = SizeType::M;
                break;
            case 2:
                size = SizeType::L;
                break;
            case 3:
                if (type != CoffeeType::CAPPUCCINO) {
                    size = SizeType::XL;
                }
                else {
                    std::cout << "Invalid size for Cappuccino.\n";
                    return;
                }
                break;
            default:
                std::cout << "Invalid size choice.\n";
                return;
            }
        }

        m_Orders[tableNumber] = createCoffee(type, size);
    }
    else if (drinkChoice == 2) {
        std::cout << "Choose a tea type:\n";
        std::cout << "1. Black Tea\n";
        std::cout << "2. Green Tea\n";
        unsigned int teaChoice;
        std::cin >> teaChoice;

        TeaType type;
        SizeType size = SizeType::NONE;

        switch (teaChoice) {
        case 1:
            type = TeaType::BLACK_TEA;
            break;
        case 2:
            type = TeaType::GREEN_TEA;
            break;
        default:
            std::cout << "Invalid choice.\n";
            return;
        }

        std::cout << "Choose a size:\n";
        std::cout << "1. M\n";
        std::cout << "2. L\n";
        unsigned int sizeChoice;
        std::cin >> sizeChoice;

        switch (sizeChoice) {
        case 1:
            size = SizeType::M;
            break;
        case 2:
            size = SizeType::L;
            break;
        default:
            std::cout << "Invalid size choice.\n";
            return;
        }

        m_Orders[tableNumber] = createTea(type, size);
    }
    else {
        std::cout << "Invalid drink choice.\n";
        return;
    }

    std::cout << "Order placed for table " << tableNumber << ".\n";
}

bool CoffeeShop::prepare(int tableNumber) {
    if (tableNumber < 0 || tableNumber >= TABLES_COUNT) {
        std::cout << "Invalid table number.\n";
        return false;
    }

    if (m_Orders[tableNumber] == nullptr) {
        std::cout << "No order for table " << tableNumber << ".\n";
        return false;
    }

    std::cout << "Preparing drink for table " << tableNumber << ".\n";
    m_Orders[tableNumber]->prepare();
    return true;
}

bool CoffeeShop::getReceipt(int tableNumber) {
    if (tableNumber < 0 || tableNumber >= TABLES_COUNT) {
        std::cout << "Invalid table number.\n";
        return false;
    }

    if (m_Orders[tableNumber] == nullptr) {
        std::cout << "No order for table " << tableNumber << ".\n";
        return false;
    }

    std::cout << "Receipt for table " << tableNumber << ":\n";
    std::cout << "Drink cost: $" << m_Orders[tableNumber]->getCost() << std::endl;
    return true;
}
