#include "coffee_shop.h"
#include <iostream>

CoffeeShop::CoffeeShop(const std::string& shopName) : name(shopName) {
    for (int i = 0; i < TABLES_COUNT; ++i) {
        m_Tables[i] = false;
        m_Orders[i] = nullptr;
    }
}

int CoffeeShop::takePlace() {
    for (int i = 0; i < TABLES_COUNT; ++i) {
        if (!m_Tables[i]) {
            m_Tables[i] = true;
            return i;
        }
    }
    return -1;
}

void CoffeeShop::order(int tableNumber) {
    if (tableNumber < 0 || tableNumber >= TABLES_COUNT || !m_Tables[tableNumber]) {
        std::cout << "Invalid table number.\n";
        return;
    }

    std::cout << "Choose a coffee type:\n";
    std::cout << "1. Espresso\n";
    std::cout << "2. Latte\n";
    std::cout << "3. Cappuccino\n";
    int choice;
    std::cin >> choice;

    CoffeeType type;
    switch (choice) {
    case 1:
        type = CoffeeType::ESPRESSO;
        break;
    case 2:
        type = CoffeeType::LATTE;
        break;
    case 3:
        type = CoffeeType::CAPPUCCINO;
        break;
    default:
        std::cout << "Invalid choice.\n";
        return;
    }

    m_Orders[tableNumber] = new Coffee(type);
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
