#pragma once

#include <SFML/Graphics.hpp>

const int ts = 54; // Tile size

class Tile {
public:
    int x, y, col, row, match, alpha;
    sf::Texture texture;
    sf::Sprite sprite;

    Tile();
    virtual void loadTexture() = 0;
    void setPosition(int col, int row);
    virtual ~Tile() = default;
};

class RedTile : public Tile {
public:
    RedTile();
    void loadTexture() override;
};

class BlueTile : public Tile {
public:
    BlueTile();
    void loadTexture() override;
};

class GreenTile : public Tile {
public:
    GreenTile();
    void loadTexture() override;
};

class YellowTile : public Tile {
public:
    YellowTile();
    void loadTexture() override;
};
