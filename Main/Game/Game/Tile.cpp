#include "Tile.h"

Tile::Tile() : match(0), alpha(255) {}

void Tile::setPosition(int col, int row) {
    this->col = col;
    this->row = row;
    x = col * ts;
    y = row * ts;
    sprite.setPosition(x, y);
}

// Red
RedTile::RedTile() : Tile() {
    loadTexture();
}

void RedTile::loadTexture() {
    texture.loadFromFile("images/NewNodes/Stage1/1.png");
    sprite.setTexture(texture);
}

// Blue
BlueTile::BlueTile() : Tile() {
    loadTexture();
}

void BlueTile::loadTexture() {
    texture.loadFromFile("images/NewNodes/Stage1/3.png");
    sprite.setTexture(texture);
}

// Green
GreenTile::GreenTile() : Tile() {
    loadTexture();
}

void GreenTile::loadTexture() {
    texture.loadFromFile("images/NewNodes/Stage1/2.png");
    sprite.setTexture(texture);
}

// Yellow
YellowTile::YellowTile() : Tile() {
    loadTexture();
}

void YellowTile::loadTexture() {
    texture.loadFromFile("images/NewNodes/Stage1/4.png");
    sprite.setTexture(texture);
}
