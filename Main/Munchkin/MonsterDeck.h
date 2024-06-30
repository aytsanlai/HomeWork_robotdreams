#pragma once

#include <vector>
#include <memory>
#include "Monster.h"

class MonsterDeck {
public:
    MonsterDeck();
    std::unique_ptr<Monster> generateMonster();

private:
    std::vector<std::unique_ptr<Monster>> monsters;
};
