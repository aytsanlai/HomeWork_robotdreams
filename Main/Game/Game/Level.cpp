#include "Level.h"
#include <cstdlib>
#include <ctime>

Level::Level(int rows, int cols) : rows(rows), cols(cols) {
    std::srand(std::time(nullptr)); // Initialize random number generator
    initializeGrid();
}

Level::~Level() {
    deleteGrid();
}

void Level::initializeGrid() {
    grid = new Tile * *[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new Tile * [cols];
        for (int j = 0; j < cols; j++) {
            int tileType = rand() % 4;
            switch (tileType) {
            case 0: grid[i][j] = new RedTile(); break;
            case 1: grid[i][j] = new BlueTile(); break;
            case 2: grid[i][j] = new GreenTile(); break;
            case 3: grid[i][j] = new YellowTile(); break;
            }
            grid[i][j]->setPosition(j * ts, i * ts); 
        }
    }
}

void Level::deleteGrid() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}

void Level::drawGrid(sf::RenderWindow& app, const sf::Vector2i& offset) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tile* p = grid[i][j];
            p->sprite.setColor(sf::Color(255, 255, 255, p->alpha));
            p->sprite.setPosition(p->x + offset.x, p->y + offset.y);
            app.draw(p->sprite);
        }
    }
}

void Level::findMatches() {
    // Find horizontal and vertical matches
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i > 0 && i < rows - 1) {
                if (grid[i][j]->kind == grid[i + 1][j]->kind && grid[i][j]->kind == grid[i - 1][j]->kind) {
                    for (int n = -1; n <= 1; n++) grid[i + n][j]->match++;
                }
            }
            if (j > 0 && j < cols - 1) {
                if (grid[i][j]->kind == grid[i][j + 1]->kind && grid[i][j]->kind == grid[i][j - 1]->kind) {
                    for (int n = -1; n <= 1; n++) grid[i][j + n]->match++;
                }
            }
        }
    }
}

bool Level::isMoving() {
    bool moving = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tile* p = grid[i][j];
            int dx = p->x - p->col * ts;
            int dy = p->y - p->row * ts;
            if (dx) p->x -= dx / std::abs(dx);
            if (dy) p->y -= dy / std::abs(dy);
            if (dx || dy) moving = true;
        }
    }
    return moving;
}

void Level::updateGrid() {
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j]->match) {
                delete grid[i][j];
                for (int n = i; n > 0; n--) {
                    if (!grid[n][j]->match) {
                        std::swap(grid[n][j], grid[i][j]);
                        break;
                    }
                }
            }
        }
    }

    for (int j = 0; j < cols; j++) {
        for (int i = rows - 1; i >= 0; i--) {
            if (grid[i][j]->match) {
                delete grid[i][j];
                int tileType = rand() % 4;
                switch (tileType) {
                case 0: grid[i][j] = new RedTile(); break;
                case 1: grid[i][j] = new BlueTile(); break;
                case 2: grid[i][j] = new GreenTile(); break;
                case 3: grid[i][j] = new YellowTile(); break;
                }
                grid[i][j]->setPosition(j * ts, i * ts);
            }
        }
    }
}

bool Level::swapTiles(int x0, int y0, int x1, int y1) {
    if (std::abs(x1 - x0) + std::abs(y1 - y0) == 1) {
        std::swap(grid[y0][x0], grid[y1][x1]);
        return true;
    }
    return false;
}

int Level::getScore() const {
    int score = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            score += grid[i][j]->match;
        }
    }
    return score;
}
