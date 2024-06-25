#pragma once
#include <string>

enum class DrinkType : uint_fast8_t { AMERICANO, LATTE, ESPRESSO, CAPPUCCINO, BLACK_TEA, GREEN_TEA };
enum class SizeType : uint_fast8_t { NONE, M, L, XL };

class Drink {
protected:
    DrinkType type;
    SizeType size;
    unsigned int cost;

public:
    explicit Drink(DrinkType t, SizeType s = SizeType::NONE);
    virtual ~Drink() = default;
    virtual void prepare() const = 0;
    [[nodiscard]] unsigned int getCost() const;
};

class Coffee : public Drink {
public:
    explicit Coffee(DrinkType t, SizeType s);
    void prepare() const override;
};

class Tea : public Drink {
public:
    explicit Tea(DrinkType t, SizeType s);
    void prepare() const override;
};
