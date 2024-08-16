#include "Modifiers.h"
#include <algorithm>
#include <vector>

BombGem::BombGem() : Tile() {
    loadTexture();
}

void BombGem::loadTexture() {
    texture.loadFromFile("images/NewNodes/Mod/Bomb.png");
    sprite.setTexture(texture);
}

void BombGem::explode(Tile* grid[10][10]) {
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 1 && i <= 8 && j >= 1 && j <= 8) {
                grid[i][j]->match++;
            }
        }
    }
}

IceBlocker::IceBlocker() : Tile() {
    loadTexture();
}

void IceBlocker::loadTexture() {
    texture.loadFromFile("images/NewNodes/Mod/Ice.png");
    sprite.setTexture(texture);
}

bool IceBlocker::isBlocking() {
    return true;
}

void shuffleGrid(Tile* grid[10][10]) {
    std::vector<Tile*> gems;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            gems.push_back(grid[i][j]);
        }
    }

    std::random_shuffle(gems.begin(), gems.end());

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            grid[i][j] = gems.back();
            grid[i][j]->setPosition(j, i);
            gems.pop_back();
        }
    }
}
