#pragma once
#include <cstdint>
#include <string>

enum class CoffeeType : uint8_t { ESPRESSO, AMERICANO, LATTE, CAPPUCCINO };
enum class TeaType : uint8_t { BLACK_TEA, GREEN_TEA };
enum class SizeType : uint8_t { NONE, M, L, XL };

class Drink {
protected:
    SizeType size;
    unsigned int cost;

public:
    explicit Drink(SizeType s = SizeType::NONE);
    virtual ~Drink() = default;
    virtual void prepare() const = 0;
    [[nodiscard]] unsigned int getCost() const;
};

class Coffee : public Drink {
private:
    CoffeeType type;

public:
    Coffee(CoffeeType t, SizeType s);
    void prepare() const override;
};

class Tea : public Drink {
private:
    TeaType type;

public:
    Tea(TeaType t, SizeType s);
    void prepare() const override;
};
