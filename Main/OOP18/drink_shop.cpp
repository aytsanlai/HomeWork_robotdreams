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

    DrinkType type;
    SizeType size = SizeType::NONE;

    if (drinkChoice == 1) {
        std::cout << "Choose a coffee type:\n";
        std::cout << "1. Espresso\n";
        std::cout << "2. Americano\n";
        std::cout << "3. Latte\n";
        std::cout << "4. Cappuccino\n";
        unsigned int coffeeChoice;
        std::cin >> coffeeChoice;

        switch (coffeeChoice) {
        case 1:
            type = DrinkType::ESPRESSO;
            size = SizeType::NONE;
            break;
        case 2:
            type = DrinkType::AMERICANO;
            break;
        case 3:
            type = DrinkType::LATTE;
            break;
        case 4:
            type = DrinkType::CAPPUCCINO;
            break;
        default:
            std::cout << "Invalid choice.\n";
            return;
        }

        if (type != DrinkType::ESPRESSO) {
            std::cout << "Choose a size:\n";
            std::cout << "1. M\n";
            std::cout << "2. L\n";
            if (type != DrinkType::CAPPUCCINO) {
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
                if (type != DrinkType::CAPPUCCINO) {
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
    }
    else if (drinkChoice == 2) {
        std::cout << "Choose a tea type:\n";
        std::cout << "1. Black Tea\n";
        std::cout << "2. Green Tea\n";
        unsigned int teaChoice;
        std::cin >> teaChoice;

        switch (teaChoice) {
        case 1:
            type = DrinkType::BLACK_TEA;
            break;
        case 2:
            type = DrinkType::GREEN_TEA;
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
    }
    else {
        std::cout << "Invalid drink choice.\n";
        return;
    }

    m_Orders[tableNumber] = createDrink(type, size);
}

bool CoffeeShop::prepare(int tableNumber) {
    if (tableNumber < 0 || tableNumber >= TABLES_COUNT || !m_Tables[tableNumber] || m_Orders[tableNumber] == nullptr) {
        return false;
    }
    m_Orders[tableNumber]->prepare();
    return true;
}

bool CoffeeShop::getReceipt(int tableNumber) {
    if (tableNumber < 0 || tableNumber >= TABLES_COUNT || !m_Tables[tableNumber] || m_Orders[tableNumber] == nullptr) {
        return false;
    }
    std::cout << "Total cost: " << m_Orders[tableNumber]->getCost() << " credits\n";
    delete m_Orders[tableNumber];
    m_Orders[tableNumber] = nullptr;
    m_Tables[tableNumber] = false;
    return true;
}
