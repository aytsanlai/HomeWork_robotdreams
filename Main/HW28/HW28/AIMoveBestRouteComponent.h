#pragma once

#include <vector>
#include "Graph.h"
#include "sfml/Graphics.hpp"

class AIMoveBestRouteComponent {
public:
    AIMoveBestRouteComponent(sf::Sprite& referenceObject, Graph& graph, float speed);
    void update(float deltaTime);
    void updatePath(sf::Vector2u destination);
    sf::Vector2u getNextTileToMove();

private:
    sf::Sprite& m_referenceObject;
    Graph& m_graph;
    std::vector<unsigned> m_path;
    float m_speed;
    sf::Vector2u m_currentTile;
    sf::Vector2u m_destinationTile;
};