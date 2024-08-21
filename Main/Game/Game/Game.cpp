#include "Game.h"
#include <ctime>
#include <algorithm>
#include <random>

Match3Game::Match3Game() : app(sf::VideoMode(1780, 960), "Match-3 Game!"), movesLeft(5), gameOver(false), gameWon(false), isReshuffling(false), click(0), isSwap(false), isMoving(false) {
    app.setFramerateLimit(100);

    t1.loadFromFile("images/background.png");
    gameOverTexture.loadFromFile("images/game_over_background.png");
    gameWonTexture.loadFromFile("images/game_won_background.png");
    shuffleTexture.loadFromFile("images/NewNodes/Mod/shuffle.png");

    background.setTexture(t1);
    gameOverBackground.setTexture(gameOverTexture);
    gameWonBackground.setTexture(gameWonTexture);
    shuffleButton.setTexture(shuffleTexture);

    offset = sf::Vector2i((app.getSize().x - GAME_SIZE * TILE_SIZE) / 2, (app.getSize().y - GAME_SIZE * TILE_SIZE) / 2);

    shuffleButton.setPosition(225, 75);
    shuffleButton.setScale(0.25f, 0.25f);

    if (!font.loadFromFile("Font/BALOO2-SEMIBOLD.TTF")) {
        // error...
    }

    movesText.setFont(font);
    movesText.setString("Moves: " + std::to_string(movesLeft));
    movesText.setCharacterSize(50);
    movesText.setFillColor(sf::Color(131, 83, 83));
    movesText.setPosition(200, 10);

    taskManager.setTask(TileType::Red, 3, "images/NewNodes/Stage3/FrogP.png");

    srand(time(0));
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
}

void Match3Game::run() {
    while (app.isOpen()) {
        sf::Event e;
        while (app.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                app.close();
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Escape) {
                    app.close();
                }
                if ((gameOver || gameWon) && e.key.code == sf::Keyboard::R) {
                    restartGame();
                    gameOver = false;
                    gameWon = false;
                    isReshuffling = false;
                }
            }

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                pos = sf::Mouse::getPosition(app) - offset;
                static constexpr unsigned int maxFieldSize = GAME_SIZE * TILE_SIZE;
                if (!isSwap && !isMoving && pos.x > 0 && pos.y > 0 && pos.x < maxFieldSize && pos.y < maxFieldSize)
                    click++;

                if (shuffleButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(app)))) {
                    reshuffleGrid();
                    isReshuffling = true;
                    soundManager.playClickSound();
                }
            }
        }

        if (click == 1) {
            colA = pos.x / TILE_SIZE;
            rowA = pos.y / TILE_SIZE;
        } else if (click == 2) {
            colB = pos.x / TILE_SIZE;
            rowB = pos.y / TILE_SIZE;
            if (abs(colB - colA) + abs(rowB - rowA) == 1) {
                swap(grid[rowA][colA], grid[rowB][colB]);
                isSwap = true;
                click = 0;
                movesLeft--;
                movesText.setString("Moves: " + std::to_string(movesLeft));
                soundManager.playClickSound();
            } else {
                click = 1;
            }
        }

        for (int row = 0; row < GAME_SIZE; row++)
            for (int col = 0; col < GAME_SIZE; col++) {
                handleMerging(row, col);
            }

        int matchCount = 0;
        for (int row = 0; row < GAME_SIZE; row++) {
            for (int col = 0; col < GAME_SIZE; col++) {
                if (grid[row][col]->isMatched && grid[row][col]->getType() == taskManager.getTaskType() && grid[row][col]->level == 3) {
                    matchCount++;
                }
            }
        }
        if (matchCount > 0) {
            taskManager.checkCompletion(taskManager.getTaskType(), matchCount);
        }

        isMoving = false;
        for (int row = 0; row < GAME_SIZE; row++) {
            for (int col = 0; col < GAME_SIZE; col++) {
                Tile* p = grid[row][col];
                int dx, dy;
                for (int n = 0; n < 4; n++) {
                    dx = p->x - p->col * TILE_SIZE;
                    dy = p->y - p->row * TILE_SIZE;
                    if (dx) p->x -= dx / abs(dx);
                    if (dy) p->y -= dy / abs(dy);
                }
                if (dx || dy) isMoving = true;
            }
        }

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

        if (isSwap && !isMoving) {
            if (!matchCount) swap(grid[rowA][colA], grid[rowB][colB]);
            isSwap = false;
        }

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

        if (isReshuffling) {
            bool allTilesInPlace = true;
            for (int row = 0; row < GAME_SIZE; row++) {
                for (int col = 0; col < GAME_SIZE; col++) {
                    Tile* p = grid[row][col];
                    int dx, dy;
                    dx = p->x - p->col * TILE_SIZE;
                    dy = p->y - p->row * TILE_SIZE;
                    if (dx) p->x -= dx / abs(dx);
                    if (dy) p->y -= dy / abs(dy);
                    if (dx || dy) allTilesInPlace = false;
                }
            }
            if (allTilesInPlace) isReshuffling = false;
        }

        if (movesLeft <= 0 && !gameOver && !gameWon) {
            gameOver = true;
        }
        if (taskManager.isTaskCompleted() && !gameOver && !gameWon) {
            gameWon = true;
        }

        app.clear();
        if (gameOver) {
            app.draw(gameOverBackground);
        } else if (gameWon) {
            app.draw(gameWonBackground);
        } else {
            app.draw(background);
            app.draw(movesText);
            taskManager.draw(app, font, sf::Vector2f(app.getSize().x - 400, 10));
            for (int row = 0; row < GAME_SIZE; row++) {
                for (int col = 0; col < GAME_SIZE; col++) {
                    Tile* p = grid[row][col];
                    p->sprite.setColor(sf::Color(255, 255, 255, p->alpha));
                    p->sprite.setPosition(p->x + offset.x, p->y + offset.y);
                    app.draw(p->sprite);
                }
            }
            if (!gameOver && !gameWon) {
                app.draw(shuffleButton);
            }
        }
        app.display();
    }
}

void Match3Game::restartGame() {
    srand(time(0));
    for (int row = 0; row < GAME_SIZE; row++) {
        for (int col = 0; col < GAME_SIZE; col++) {
            delete grid[row][col];
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
    movesLeft = 30;
    taskManager.setTask(TileType::Red, 3, "images/NewNodes/Stage3/FrogP.png");
}

void Match3Game::reshuffleGrid() {
    std::vector<Tile*> tiles;
    for (int row = 0; row < GAME_SIZE; row++) {
        for (int col = 0; col < GAME_SIZE; col++) {
            tiles.push_back(grid[row][col]);
        }
    }
    std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine(std::time(0)));
    for (int i = 0; i < tiles.size(); i++) {
        int row = i / GAME_SIZE;
        int col = i % GAME_SIZE;
        tiles[i]->row = row;
        tiles[i]->col = col;
        tiles[i]->y = -TILE_SIZE * (GAME_SIZE - row);
        grid[row][col] = tiles[i];
    }

    for (int row = 0; row < GAME_SIZE; row++) {
        for (int col = 0; col < GAME_SIZE; col++) {
            const unsigned int TileType = rand() % 4;
            switch (TileType) {
                case 0:
                    delete grid[row][col];
                    grid[row][col] = new RedTile(row, col);
                    break;
                case 1:
                    delete grid[row][col];
                    grid[row][col] = new BlueTile(row, col);
                    break;
                case 2:
                    delete grid[row][col];
                    grid[row][col] = new GreenTile(row, col);
                    break;
                case 3:
                    delete grid[row][col];
                    grid[row][col] = new YellowTile(row, col);
                    break;
            }
        }
    }
}

void Match3Game::swap(Tile* p1, Tile* p2) {
    std::swap(p1->col, p2->col);
    std::swap(p1->row, p2->row);
    grid[p1->row][p1->col] = p1;
    grid[p2->row][p2->col] = p2;
}

void Match3Game::handleMerging(int row, int col) {
    if (row + 1 < GAME_SIZE && row - 1 >= 0 && *grid[row][col] == *grid[row + 1][col] && *grid[row][col] == *grid[row - 1][col]) {
        grid[row][col]->merge();
        grid[row + 1][col]->isMatched = true;
        grid[row - 1][col]->isMatched = true;
        grid[row][col]->animateMerge();
        soundManager.playMergeSound();
    }
    if (col + 1 < GAME_SIZE && col - 1 >= 0 && *grid[row][col] == *grid[row][col + 1] && *grid[row][col] == *grid[row][col - 1]) {
        grid[row][col]->merge();
        grid[row][col + 1]->isMatched = true;
        grid[row][col - 1]->isMatched = true;
        grid[row][col]->animateMerge();
        soundManager.playMergeSound();
    }
}