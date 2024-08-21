#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <string>
#include <memory>

constexpr int TILE_SIZE = 100; // Tile size

enum class TileType : std::uint_fast8_t {
    Red,
    Blue,
    Green,
    Yellow
};

class Tile {
public:
    Tile(int row, int col, const std::string& textureFile, TileType type, int width = TILE_SIZE, int height = TILE_SIZE, int level = 1);
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
    void merge(); // New method to handle merging
    void animateMerge(); // New method to handle merge animation

    int x = 0, y = 0, col = 0, row = 0, alpha = 255;
    sf::Sprite sprite;
    bool isMatched = false;
    int level = 1; // New level variable

private:
    void loadTexture(const std::string& textureFile);
    std::string levelToTextureFile() const; // Method to get texture file based on level

    std::unique_ptr<sf::Texture> texture;
    TileType type;
};

class RedTile : public Tile {
public:
    explicit RedTile(int row, int col, int level = 1);
};

class BlueTile : public Tile {
public:
    explicit BlueTile(int row, int col, int level = 1);
};

class GreenTile : public Tile {
public:
    explicit GreenTile(int row, int col, int level = 1);
};

class YellowTile : public Tile {
public:
    explicit YellowTile(int row, int col, int level = 1);
};
