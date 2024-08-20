#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include "TaskManager.h"
#include "SoundManager.h"

class Match3Game {
public:
    Match3Game();
    void run();
    void restartGame();
    void reshuffleGrid();
    void swap(Tile* p1, Tile* p2);
    void handleMerging(int row, int col);

private:
    static constexpr uint_fast8_t GAME_SIZE = 8;
    Tile* grid[GAME_SIZE][GAME_SIZE];
    TaskManager taskManager;
    SoundManager soundManager;
    sf::RenderWindow app;
    sf::Font font;
    sf::Text movesText;
    sf::Texture t1, gameOverTexture, gameWonTexture, shuffleTexture;
    sf::Sprite background, gameOverBackground, gameWonBackground, shuffleButton;
    sf::Vector2i offset;
    int movesLeft;
    bool gameOver;
    bool gameWon;
    bool isReshuffling;
    int colA, rowA, colB, rowB;
    int click;
    sf::Vector2i pos;
    bool isSwap;
    bool isMoving;
};

#endif // GAME_H