#pragma once

#include "Tile.h"

class BombGem : public Tile {
public:
    BombGem();
    void loadTexture() override;
    void explode(Tile* grid[10][10]);
};

class IceBlocker : public Tile {
public:
    IceBlocker();
    void loadTexture() override;
    bool isBlocking();
};

void shuffleGrid(Tile* grid[10][10]);
