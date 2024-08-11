#pragma once
#include "Component.h"
#include "Graph.h"

//Comment it out to remove Visual GRAPH debug functionality
#define DEBUG_PATH
//#define DEBUG_VERTEX

class GameObject;

class AIMoveBestRouteComponent : public AIMoveToComponent
{
public:
    AIMoveBestRouteComponent(GameObject* referenceObject, GameObject* targetObject);

    void update(float dt) override;
    void draw(sf::RenderWindow* window) override;

private:
    Graph buildGraph();
    void updatePath(Graph& graph);
    sf::Vector2u getNextTileToMove();

    sf::Vector2u convertVertixToMapTile(unsigned vertix) const;
    unsigned convertMapTileToVertix(sf::Vector2u mapTile) const;

private:
    Graph m_mapGraph;
    std::vector<unsigned> m_path;

#ifdef DEBUG_VERTEX
    sf::Text m_text;
#endif
};
