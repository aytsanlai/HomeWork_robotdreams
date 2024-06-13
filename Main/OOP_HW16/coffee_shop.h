#pragma once
#include <string>
#include "coffee.h"

const int TABLES_COUNT = 10;

class CoffeeShop {
private:
    std::string name;
    bool m_Tables[TABLES_COUNT];
    Coffee* m_Orders[TABLES_COUNT];

public:
    CoffeeShop(const std::string& shopName);

    int takePlace();

    void order(int tableNumber);

    bool prepare(int tableNumber);

    bool getReceipt(int tableNumber);
};
