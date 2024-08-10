#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>

class Map {
public:
    using TilesMapType = std::vector<std::vector<int>>;

    static const TilesMapType R_AND_D_MAP;
    static const TilesMapType PACMAN_MAP1;
    static const TilesMapType PACMAN_MAP2;

    Map();
    bool isTileBlocked(const sf::Vector2f& position) const;
    bool isPositionInTile(const sf::Vector2f& position, const sf::Vector2u& tile) const;
    sf::Vector2f getRandomValidPosition() const;
    sf::Vector2f getPositionFromTile(const sf::Vector2u& tile) const;
    sf::Vector2u getTileFromPosition(const sf::Vector2f& gameObjectPosition) const;
    void draw(sf::RenderWindow* window);

private:
    std::vector<sf::RectangleShape> m_tilesShapes;
    TilesMapType m_tilesMap;
    int TILE_WIDTH;
    int TILE_HEIGHT;
};

#endif 