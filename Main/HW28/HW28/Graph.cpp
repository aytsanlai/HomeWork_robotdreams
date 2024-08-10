#include "Graph.h"
#include <queue>
#include <unordered_set>

Graph::Graph(const Map::TilesMapType& tilesMap, int tileWidth, int tileHeight)
    : m_tileWidth(tileWidth), m_tileHeight(tileHeight) {
    m_adjacencyList.resize(tilesMap.size() * tilesMap[0].size());

    for (unsigned y = 0; y < tilesMap.size(); ++y) {
        for (unsigned x = 0; x < tilesMap[y].size(); ++x) {
            if (tilesMap[y][x] == 0) {
                unsigned currentIndex = y * tilesMap[0].size() + x;

                
                if (x > 0 && tilesMap[y][x - 1] == 0) {
                    m_adjacencyList[currentIndex].push_back(y * tilesMap[0].size() + x - 1);
                }
                if (x < tilesMap[y].size() - 1 && tilesMap[y][x + 1] == 0) {
                    m_adjacencyList[currentIndex].push_back(y * tilesMap[0].size() + x + 1);
                }
                if (y > 0 && tilesMap[y - 1][x] == 0) {
                    m_adjacencyList[currentIndex].push_back((y - 1) * tilesMap[0].size() + x);
                }
                if (y < tilesMap.size() - 1 && tilesMap[y + 1][x] == 0) {
                    m_adjacencyList[currentIndex].push_back((y + 1) * tilesMap[0].size() + x);
                }
            }
        }
    }
}

void Graph::addEdge(unsigned x, unsigned y) {
    m_adjacencyList[x].push_back(y);
}

std::vector<unsigned> Graph::bfs(unsigned start, unsigned destination) {
    std::queue<unsigned> queue;
    std::unordered_set<unsigned> visited;
    std::vector<unsigned> parent(m_adjacencyList.size(), -1);

    queue.push(start);
    visited.insert(start);

    while (!queue.empty()) {
        unsigned currentIndex = queue.front();
        queue.pop();

        if (currentIndex == destination) {
          
            std::vector<unsigned> path;
            while (currentIndex != -1) {
                path.push_back(currentIndex);
                currentIndex = parent[currentIndex];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (unsigned neighbor : m_adjacencyList[currentIndex]) {
            if (!visited.count(neighbor)) {
                queue.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = currentIndex;
            }
        }
    }

    
    return {};
}