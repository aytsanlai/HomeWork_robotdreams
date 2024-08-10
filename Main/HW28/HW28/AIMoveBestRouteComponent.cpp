#include "AIMoveBestRouteComponent.h"
#include "Map.h"

AIMoveBestRouteComponent::AIMoveBestRouteComponent(sf::Sprite& referenceObject, Graph& graph, float speed)
    : m_referenceObject(referenceObject), m_graph(graph), m_speed(speed) {
    m_currentTile = Map::GetInstance().getTileFromPosition(m_referenceObject.getPosition());
}

void AIMoveBestRouteComponent::update(float deltaTime) {
    if (!m_path.empty()) {
        m_destinationTile = { m_path[1] % Map::GetInstance().getMapWidth(), m_path[1] / Map::GetInstance().getMapWidth() };
        sf::Vector2f direction = sf::Vector2f(m_destinationTile.x * Map::GetInstance().getTileSize(), m_destinationTile.y * Map::GetInstance().getTileSize()) - m_referenceObject.getPosition();
        direction /= sqrtf(powf(direction.x, 2) + powf(direction.y, 2));
        m_referenceObject.move(direction * m_speed * deltaTime);

        if (sqrtf(powf(m_referenceObject.getPosition().x - m_destinationTile.x * Map::GetInstance().getTileSize(), 2) + powf(m_referenceObject.getPosition().y - m_destinationTile.y * Map::GetInstance().getTileSize(), 2)) < 1.0f) {
            m_path.erase(m_path.begin());
            if (m_path.empty()) {
                m_currentTile = m_destinationTile;
            }
        }
    }
}

void AIMoveBestRouteComponent::updatePath(sf::Vector2u destination) {
    unsigned start = m_currentTile.x + m_currentTile.y * Map::GetInstance().getMapWidth();
    unsigned dest = destination.x + destination.y * Map::GetInstance().getMapWidth();
    m_path = m_graph.bfs(start, dest);
}

sf::Vector2u AIMoveBestRouteComponent::getNextTileToMove() {
    if (m_path.size() < 2) {
        return m_currentTile;
    }

    unsigned nextTile = m_path[1];
    return { nextTile % Map::GetInstance().getMapWidth(), nextTile / Map::GetInstance().getMapWidth() };
}