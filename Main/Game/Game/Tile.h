#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <string>
#include <memory>

constexpr int TILE_SIZE = 64; // Tile size

enum class TileType : std::uint_fast8_t {
    Red,
    Blue,
    Green,
    Yellow
};

class Tile {
public:
    Tile(int row, int col, const std::string& textureFile, TileType type, int width = TILE_SIZE, int height = TILE_SIZE);
    virtual ~Tile() = default;

    // Delete copy constructor and copy assignment operator
    Tile(const Tile&) = delete;
    Tile& operator=(const Tile&) = delete;

    // Default move constructor and move assignment operator
    Tile(Tile&&) noexcept = default;
    Tile& operator=(Tile&&) noexcept = default;

    void setPosition(int row, int col) noexcept;
    sf::Sprite& getSprite() noexcept;
    TileType getType() const noexcept;
    bool operator==(const Tile& other) const noexcept;
    void setSize(int width, int height);

    int x = 0, y = 0, col = 0, row = 0, alpha = 255;
    sf::Sprite sprite;
    bool isMatched = false;

private:
    void loadTexture(const std::string& textureFile);

    std::unique_ptr<sf::Texture> texture;
    TileType type;
};

class RedTile : public Tile {
public:
    explicit RedTile(int row, int col);
};

class BlueTile : public Tile {
public:
    explicit BlueTile(int row, int col);
};

class GreenTile : public Tile {
public:
    explicit GreenTile(int row, int col);
};

class YellowTile : public Tile {
public:
    explicit YellowTile(int row, int col);
};