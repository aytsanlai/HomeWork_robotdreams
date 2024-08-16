#include <SFML/Graphics.hpp>
#include <time.h>
#include "Tile.h"
#include "Modifiers.h"

using namespace sf;

Vector2i offset(48, 24);

void swap(Tile* p1, Tile* p2) {
    std::swap(p1->col, p2->col);
    std::swap(p1->row, p2->row);
    std::swap(p1, p2);
}

int main() {
    srand(time(0));

    RenderWindow app(VideoMode(1780, 960), "Match-3 Game!");
    app.setFramerateLimit(60);

    Texture t1;
    t1.loadFromFile("images/background.png");
    Sprite background(t1);

    Tile* grid[10][10];

    // Initialize grid with random tiles
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            int TileType = rand() % 4;
            switch (TileType) {
            case 0: grid[i][j] = new RedTile(); break;
            case 1: grid[i][j] = new BlueTile(); break;
            case 2: grid[i][j] = new GreenTile(); break;
            case 3: grid[i][j] = new YellowTile(); break;
            }
            grid[i][j]->setPosition(j, i);
        }
    }

    int x0, y0, x, y;
    int click = 0;
    Vector2i pos;
    bool isSwap = false, isMoving = false;

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) {
                    if (!isSwap && !isMoving) click++;
                    pos = Mouse::getPosition(app) - offset;
                }
        }

        // Mouse click handling
        if (click == 1) {
            x0 = pos.x / ts + 1;
            y0 = pos.y / ts + 1;
        }
        if (click == 2) {
            x = pos.x / ts + 1;
            y = pos.y / ts + 1;
            if (abs(x - x0) + abs(y - y0) == 1) {
                swap(grid[y0][x0], grid[y][x]);
                isSwap = true;
                click = 0;
            }
            else {
                click = 1;
            }
        }

        //Match finding
        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
            {
                if (grid[i][j].kind == grid[i + 1][j].kind)
                    if (grid[i][j].kind == grid[i - 1][j].kind)
                        for (int n = -1; n <= 1; n++) grid[i + n][j].match++;

                if (grid[i][j].kind == grid[i][j + 1].kind)
                    if (grid[i][j].kind == grid[i][j - 1].kind)
                        for (int n = -1; n <= 1; n++) grid[i][j + n].match++;
            }

        // Moving animation
        isMoving = false;
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                Tile* p = grid[i][j];
                int dx, dy;
                for (int n = 0; n < 4; n++) { // 4 - speed
                    dx = p->x - p->col * ts;
                    dy = p->y - p->row * ts;
                    if (dx) p->x -= dx / abs(dx);
                    if (dy) p->y -= dy / abs(dy);
                }
                if (dx || dy) isMoving = true;
            }
        }

        // Deleting animation
        if (!isMoving) {
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    if (grid[i][j]->match) {
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
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                score += grid[i][j]->match;
            }
        }

        // Second swap if no match
        if (isSwap && !isMoving) {
            if (!score) swap(grid[y0][x0], grid[y][x]);
            isSwap = false;
        }

        // Update grid after deletion
        if (!isMoving) {
            for (int i = 8; i >= 1; i--) {
                for (int j = 1; j <= 8; j++) {
                    if (grid[i][j]->match) {
                        delete grid[i][j];
                        for (int n = i; n > 0; n--) {
                            if (!grid[n][j]->match) {
                                swap(grid[n][j], grid[i][j]);
                                break;
                            }
                        }
                    }
                }
            }

            // Generate new gems
            for (int j = 1; j <= 8; j++) {
                for (int i = 8, n = 0; i >= 1; i--) {
                    if (grid[i][j]->match) {
                        delete grid[i][j];
                        int gemType = rand() % 4;
                        switch (gemType) {
                        case 0: grid[i][j] = new RedTile(); break;
                        case 1: grid[i][j] = new BlueTile(); break;
                        case 2: grid[i][j] = new GreenTile(); break;
                        case 3: grid[i][j] = new YellowTile(); break;
                        }
                        grid[i][j]->setPosition(j, i);
                    }
                }
            }
        }

        // Drawing
        app.clear();
        app.draw(background);
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                Tile* p = grid[i][j];
                p->sprite.setColor(Color(255, 255, 255, p->alpha));
                p->sprite.setPosition(p->x, p->y);
                p->sprite.move(offset.x - ts, offset.y - ts);
                app.draw(p->sprite);
            }
        }

        app.display();
    }

    return 0;
}
