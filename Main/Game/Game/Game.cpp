#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cstdint>
#include <time.h>
#include <iostream>
#include "Tile.h"

using namespace sf;

const Vector2i offset(TILE_SIZE, TILE_SIZE);
constexpr uint_fast8_t GAME_SIZE = 8;
Tile* grid[GAME_SIZE][GAME_SIZE];

void swap(Tile* p1, Tile* p2) {
    std::swap(p1->col, p2->col);
    std::swap(p1->row, p2->row);
    grid[p1->row][p1->col] = p1;
    grid[p2->row][p2->col] = p2;
}

void handleMerging(int row, int col) {
    // Check for merging conditions
    if (row + 1 < GAME_SIZE && row - 1 >= 0 && *grid[row][col] == *grid[row + 1][col] && *grid[row][col] == *grid[row - 1][col]) {
        // Merge tiles
        grid[row][col]->merge();
        grid[row + 1][col]->isMatched = true;
        grid[row - 1][col]->isMatched = true;
        grid[row][col]->animateMerge();
    }
    if (col + 1 < GAME_SIZE && col - 1 >= 0 && *grid[row][col] == *grid[row][col + 1] && *grid[row][col] == *grid[row][col - 1]) {
        // Merge tiles
        grid[row][col]->merge();
        grid[row][col + 1]->isMatched = true;
        grid[row][col - 1]->isMatched = true;
        grid[row][col]->animateMerge();
    }
}

int main() {
    srand(time(0));

    RenderWindow app(VideoMode(1780, 960), "Match-3 Game!");
    app.setFramerateLimit(100);

    Texture t1;
    t1.loadFromFile("images/background.png");
    Sprite background(t1);

    const Vector2i offset((app.getSize().x - GAME_SIZE * TILE_SIZE) / 2, (app.getSize().y - GAME_SIZE * TILE_SIZE) / 2);

    // Initialize grid with random tiles
    for (int row = 0; row < GAME_SIZE; row++) {
        for (int col = 0; col < GAME_SIZE; col++) {
            const unsigned int TileType = rand() % 4;
            switch (TileType) {
            case 0:
                grid[row][col] = new RedTile(row, col);
                break;
            case 1:
                grid[row][col] = new BlueTile(row, col);
                break;
            case 2:
                grid[row][col] = new GreenTile(row, col);
                break;
            case 3:
                grid[row][col] = new YellowTile(row, col);
                break;
            }
        }
    }

    int colA, rowA, colB, rowB;
    int click = 0;
    Vector2i pos;
    bool isSwap = false, isMoving = false;

    // Moves mechanic
    sf::Font font;
    sf::Text movesText;
    int movesLeft = 5; // Initial number of moves

    if (!font.loadFromFile("Font/BALOO2-SEMIBOLD.TTF")) {
        // error...
        return -1;
    }

    movesText.setFont(font);
    movesText.setString("Moves: " + std::to_string(movesLeft));
    movesText.setCharacterSize(24); // in pixels, not points!
    movesText.setFillColor(sf::Color::White);
    movesText.setPosition(10, 10); // Top-left corner

    while (app.isOpen() && movesLeft > 0) { // Check if moves are left
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Escape) {
                    app.close();
                }
            }

            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
                pos = Mouse::getPosition(app) - offset;
                static constexpr unsigned int maxFieldSize = GAME_SIZE * TILE_SIZE;
                if (!isSwap && !isMoving && pos.x > 0 && pos.y > 0 && pos.x < maxFieldSize &&
                    pos.y < maxFieldSize)
                    click++;
            }
        }

        // Mouse click handling
        if (click == 1) {
            colA = pos.x / TILE_SIZE;
            rowA = pos.y / TILE_SIZE;
        }
        else if (click == 2) {
            colB = pos.x / TILE_SIZE;
            rowB = pos.y / TILE_SIZE;
            if (abs(colB - colA) + abs(rowB - rowA) == 1) {
                swap(grid[rowA][colA], grid[rowB][colB]);
                isSwap = true;
                click = 0;
                movesLeft--; // Decrease the moves counter
                movesText.setString("Moves: " + std::to_string(movesLeft)); // Update the text
            }
            else {
                click = 1;
            }
        }

        // Match finding and merging
        for (int row = 0; row < GAME_SIZE; row++)
            for (int col = 0; col < GAME_SIZE; col++) {
                handleMerging(row, col);
            }

        // Moving animation
        isMoving = false;
        for (int row = 0; row < GAME_SIZE; row++) {
            for (int col = 0; col < GAME_SIZE; col++) {
                Tile* p = grid[row][col];
                int dx, dy;
                for (int n = 0; n < 4; n++) { // 4 - speed
                    dx = p->x - p->col * TILE_SIZE;
                    dy = p->y - p->row * TILE_SIZE;
                    if (dx) p->x -= dx / abs(dx);
                    if (dy) p->y -= dy / abs(dy);
                }
                if (dx || dy) isMoving = true;
            }
        }

        // Deleting animation
        if (!isMoving) {
            for (int i = 0; i < GAME_SIZE; i++) {
                for (int j = 0; j < GAME_SIZE; j++) {
                    if (grid[i][j]->isMatched) {
                        if (grid[i][j]->alpha > 10) {
                            grid[i][j]->alpha -= 10;
                            isMoving = true;
                        }
                    }
                }
            }
        }

        // Get score
        int score = 0;
        for (int i = 0; i < GAME_SIZE; i++) {
            for (int j = 0; j < GAME_SIZE; j++) {
                score += grid[i][j]->isMatched;
            }
        }

        // Second swap if no match
        if (isSwap && !isMoving) {
            if (!score) swap(grid[rowA][colA], grid[rowB][colB]);
            isSwap = false;
        }

        // Update grid after deletion
        if (!isMoving) {
            for (int row = GAME_SIZE - 1; row > 0; row--) {
                for (int col = 0; col < GAME_SIZE; col++) {
                    if (grid[row][col]->isMatched) {
                        for (int rowGoingUp = row - 1; rowGoingUp >= 0; rowGoingUp--) {
                            if (!grid[rowGoingUp][col]->isMatched) {
                                swap(grid[rowGoingUp][col], grid[row][col]);
                                break;
                            }
                        }
                    }
                }
            }

            // Generate new gems
            for (int row = 0; row < GAME_SIZE; row++) {
                for (int col = GAME_SIZE - 1; col >= 0; col--) {
                    if (grid[row][col]->isMatched) {
                        const unsigned int gemType = rand() % 4;
                        switch (gemType) {
                        case 0:
                            grid[row][col] = new RedTile(row, col);
                            break;
                        case 1:
                            grid[row][col] = new BlueTile(row, col);
                            break;
                        case 2:
                            grid[row][col] = new GreenTile(row, col);
                            break;
                        case 3:
                            grid[row][col] = new YellowTile(row, col);
                            break;
                        }
                        grid[row][col]->y = -TILE_SIZE * (GAME_SIZE - row);
                    }
                }
            }
        }

        // Drawing
        app.clear();
        app.draw(background);
        app.draw(movesText); // Draw the moves text
        for (int row = 0; row < GAME_SIZE; row++) {
            for (int col = 0; col < GAME_SIZE; col++) {
                Tile* p = grid[row][col];
                p->sprite.setColor(Color(255, 255, 255, p->alpha));
                p->sprite.setPosition(p->x + offset.x, p->y + offset.y);
                app.draw(p->sprite);
            }
        }

        app.display();
    }

    // If the game ends because of no moves left, display a message
    if (movesLeft <= 0) {
        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over! No moves left.");
        gameOverText.setCharacterSize(48);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(app.getSize().x / 2 - gameOverText.getLocalBounds().width / 2, app.getSize().y / 2 - gameOverText.getLocalBounds().height / 2);

        app.clear();
        app.draw(background);
        app.draw(gameOverText);
        app.display();

        // Wait for a few seconds before closing the window
        sf::sleep(sf::seconds(3));
    }

    return 0;
}
