#pragma once
#include <string>
#include "drink.h"

using TableSizeType = uint_fast8_t;

constexpr TableSizeType TABLES_COUNT = 10;

class CoffeeShop {
private:
    std::string name;
    bool m_Tables[TABLES_COUNT]{};
    Drink* m_Orders[TABLES_COUNT]{};

public:
    explicit CoffeeShop(std::string shopName);

    int takePlace();

    void order(int tableNumber);

    bool prepare(int tableNumber);

    bool getReceipt(int tableNumber);
};
