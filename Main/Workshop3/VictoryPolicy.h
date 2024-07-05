#pragma once

#include "Game.h"

class VictoryPolicy {
public:
    virtual void apply(Game &game) = 0;
    virtual ~VictoryPolicy() = default;
};