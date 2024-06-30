#pragma once

#include <vector>
#include <memory>
#include "Modifier.h"

class ModifierDeck {
public:
    ModifierDeck();
    std::unique_ptr<Modifier> generateModifier();

private:
    std::vector<std::unique_ptr<Modifier>> modifiers;
};
