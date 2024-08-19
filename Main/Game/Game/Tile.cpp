#include "Tile.h"
#include <stdexcept>
#include <iostream>

// Tile base class
Tile::Tile(int row, int col, const std::string& textureFile, TileType type, int width, int height, int level)
    : col(col), row(row), type(type), level(level) {
    setPosition(row, col);
    loadTexture(textureFile);
    setSize(width, height);
}

void Tile::setPosition(int row, int col) noexcept {
    this->col = col;
    this->row = row;
    x = row * TILE_SIZE;
    y = col * TILE_SIZE;
    sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
}

sf::Sprite& Tile::getSprite() noexcept {
    return sprite;
}

TileType Tile::getType() const noexcept {
    return type;
}

void Tile::loadTexture(const std::string& textureFile) {
    texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load texture: " + textureFile);
    }
    sprite.setTexture(*texture);
}

void Tile::setSize(int width, int height) {
    // Get the original size of the texture
    const sf::Vector2u textureSize = texture->getSize();

    // Calculate the scale factors to resize the sprite
    const float scaleX = static_cast<float>(width) / textureSize.x;
    const float scaleY = static_cast<float>(height) / textureSize.y;

    // Set the scale of the sprite
    sprite.setScale(scaleX, scaleY);
}

bool Tile::operator==(const Tile& other) const noexcept {
    return type == other.type;
}

void Tile::merge() {
    if (level < 2) {
        level++;
        loadTexture(levelToTextureFile());
    }
}

void Tile::animateMerge() {
    // Implement merge animation logic here
}

std::string Tile::levelToTextureFile() const {
    switch (type) {
    case TileType::Red:
        return level == 1 ? "images/NewNodes/Stage1/1.png" : "images/NewNodes/Stage2/Frog.png";
    case TileType::Blue:
        return level == 1 ? "images/NewNodes/Stage1/3.png" : "images/NewNodes/Stage2/Heart.png";
    case TileType::Green:
        return level == 1 ? "images/NewNodes/Stage1/2.png" : "images/NewNodes/Stage2/Moon.png";
    case TileType::Yellow:
        return level == 1 ? "images/NewNodes/Stage1/4.png" : "images/NewNodes/Stage2/Mushroom.png";
    default:
        throw std::runtime_error("Unknown tile type");
    }
}

// RedTile
RedTile::RedTile(int row, int col, int level)
    : Tile(row, col, "images/NewNodes/Stage1/1.png", TileType::Red, TILE_SIZE, TILE_SIZE, level) {}

// BlueTile
BlueTile::BlueTile(int row, int col, int level)
    : Tile(row, col, "images/NewNodes/Stage1/3.png", TileType::Blue, TILE_SIZE, TILE_SIZE, level) {}

// GreenTile
GreenTile::GreenTile(int row, int col, int level)
    : Tile(row, col, "images/NewNodes/Stage1/2.png", TileType::Green, TILE_SIZE, TILE_SIZE, level) {}

// YellowTile
YellowTile::YellowTile(int row, int col, int level)
    : Tile(row, col, "images/NewNodes/Stage1/4.png", TileType::Yellow, TILE_SIZE, TILE_SIZE, level) {}
