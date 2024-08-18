#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Modifiers.h"

class Level {
public:
    Level(int rows, int cols);
    ~Level();

    void initializeGrid();
    void deleteGrid();
    void drawGrid(sf::RenderWindow& app, const sf::Vector2i& offset);
    void updateGrid();
    void findMatches();
    bool isMoving();
    bool swapTiles(int x0, int y0, int x1, int y1);
    int getScore() const;

private:
    int rows;
    int cols;
    Tile*** grid;
};
