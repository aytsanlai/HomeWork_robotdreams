#pragma once

#include <vector>
#include <list>
#include <SFML/Graphics.hpp>

class Graph {
public:
    Graph(const Map::TilesMapType& tilesMap, int tileWidth, int tileHeight);
    void addEdge(unsigned x, unsigned y);
    std::vector<unsigned> bfs(unsigned start, unsigned destination);

private:
    std::vector<std::list<unsigned>> m_adjacencyList;
    int m_tileWidth;
    int m_tileHeight;
};