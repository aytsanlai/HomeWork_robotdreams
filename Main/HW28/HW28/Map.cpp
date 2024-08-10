#include "Map.h"
#include "assert.h"

const Map::TilesMapType Map::R_AND_D_MAP =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,1,1,1,0,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,0,0,0,1,0,0,0,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const Map::TilesMapType Map::PACMAN_MAP1 =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1},
    {1,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const Map::TilesMapType Map::PACMAN_MAP2 =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Map::Map() : TILE_WIDTH(30), TILE_HEIGHT(30) {
    m_tilesMap = PACMAN_MAP1;
    createTilesShapes();
}

bool Map::isTileBlocked(const sf::Vector2f& position) const {
    sf::Vector2u tilePosition = getTileFromPosition(position);
    return m_tilesMap[tilePosition.y][tilePosition.x] == 1;
}

bool Map::isPositionInTile(const sf::Vector2f& position, const sf::Vector2u& tile) const {
    sf::Vector2f tilePosition = getPositionFromTile(tile);
    return position.x >= tilePosition.x && position.x < tilePosition.x + TILE_WIDTH &&
        position.y >= tilePosition.y && position.y < tilePosition.y + TILE_HEIGHT;
}

sf::Vector2f Map::getRandomValidPosition() const {
    sf::Vector2u randomTile;
    do {
        randomTile.x = rand() % m_tilesMap[0].size();
        randomTile.y = rand() % m_tilesMap.size();
    } while (m_tilesMap[randomTile.y][randomTile.x] == 1);
    return getPositionFromTile(randomTile);
}

sf::Vector2f Map::getPositionFromTile(const sf::Vector2u& tile) const {
    return sf::Vector2f(tile.x * TILE_WIDTH, tile.y * TILE_HEIGHT);
}

sf::Vector2u Map::getTileFromPosition(const sf::Vector2f& gameObjectPosition) const {
    return sf::Vector2u(gameObjectPosition.x / TILE_WIDTH, gameObjectPosition.y / TILE_HEIGHT);
}

void Map::draw(sf::RenderWindow* window) {
    for (const auto& tileShape : m_tilesShapes) {
        window->draw(tileShape);
    }
}

void Map::createTilesShapes() {
    m_tilesShapes.clear();
    for (unsigned int y = 0; y < m_tilesMap.size(); ++y) {
        for (unsigned int x = 0; x < m_tilesMap[y].size(); ++x) {
            if (m_tilesMap[y][x] == 1) {
                sf::RectangleShape tileShape(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
                tileShape.setPosition(x * TILE_WIDTH, y * TILE_HEIGHT);
                tileShape.setFillColor(sf::Color::Blue);
                m_tilesShapes.push_back(tileShape);
            }
        }
    }
}