#pragma once

#include <cstdint>
class Drink;
class Coffee;
class Tea;
enum class CoffeeType : uint8_t;
enum class TeaType : uint8_t;
enum class SizeType : uint8_t;

Drink* createCoffee(CoffeeType type, SizeType size);
Drink* createTea(TeaType type, SizeType size);